#include<assert.h>

#include "serial_link.h"

///enable this to print debug data
#define DEBUG_PRINT printf
#define printtime printtime
//#define DEBUG_PRINT(...)
//#define printtime(...)
#define DEBUG_PRINT2 printf
//#define DEBUG_PRINT2(...)
#define pthread_mutex_lock(x) {printf("%s: pthread_mutex_lock(%s) at ",__func__, #x); printtime(); pthread_mutex_lock(x);}
#define pthread_mutex_unlock(x) {printf("%s: pthread_mutex_unlock(%s) at ",__func__, #x); printtime(); pthread_mutex_unlock(x);}
#define pthread_cond_signal(x) {printf("%s: pthread_cond_signal(%s) at ",__func__, #x); printtime(); pthread_cond_signal(x);}
#define pthread_cond_wait(x, xl) {printf("%s: pthread_cond_wait(%s, %s) at ",__func__, #x, #xl); printtime(); pthread_cond_wait(x, xl);}

void sl_init(sl_device *sl_dev)
{
  sl_dev->status = 0;
  sl_dev->req_cmd = -1;
  pthread_mutex_init(&sl_dev->write_return_cond_lock, NULL);
  pthread_cond_init(&sl_dev->write_return_cond, NULL);
  pthread_mutex_init(&sl_dev->status_clear_cond_lock, NULL);
  pthread_cond_init(&sl_dev->status_clear_cond, NULL);
}

int sl_start(sl_device *sl_dev, const char *serial_port, const uint32_t baud_rate)
{
  int ret = serial_init(&(sl_dev->sdev), serial_port, baud_rate);

  if(ret > 0)
  {
    sl_dev->running_thread = true;
    pthread_create(&(sl_dev->read_thread), NULL, sl_read_thread, (void*) (sl_dev));
  }
  return ret;
}

int _sl_write_cmd(sl_device *sl_dev, const struct cmd* sent_cmd, const uint8_t sent_cmd_nbytes, struct cmd* ret_cmd)
{
  uint8_t ret;

  for(;;) {
    pthread_mutex_lock(&sl_dev->write_return_cond_lock);

    if(sl_dev->status==0) {
      ret=serial_write(&sl_dev->sdev, (uint8_t*)sent_cmd, sent_cmd_nbytes);

      if(ret!=sent_cmd_nbytes) {
	pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
	fprintf(stderr,"%s: Error: Wrote %u/%u bytes!\n",__func__,ret,sent_cmd_nbytes);
	return ret;

      } else {

	if(ret_cmd) __atomic_store_n(&sl_dev->req_cmd, ret_cmd->id, __ATOMIC_SEQ_CST);
	pthread_cond_wait(&sl_dev->write_return_cond, &sl_dev->write_return_cond_lock);

	//If status is no longer cleared
	if(sl_dev->status!=0) {
	  pthread_mutex_lock(&sl_dev->status_clear_cond_lock);
	  pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
	  pthread_cond_wait(&sl_dev->status_clear_cond, &sl_dev->status_clear_cond_lock);
	  pthread_mutex_unlock(&sl_dev->status_clear_cond_lock);
	  continue;

	//If the link is still in sync and the command returned
	} else {

	  if(ret_cmd) {
	    __atomic_store_n(&sl_dev->req_cmd, -1, __ATOMIC_SEQ_CST);
	    *ret_cmd=sl_dev->ret_cmd;
	  }
	  pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
	  return 0;
	}
      }

    //If status was not cleared
    } else {
      pthread_mutex_lock(&sl_dev->status_clear_cond_lock);
      pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
      pthread_cond_wait(&sl_dev->status_clear_cond, &sl_dev->status_clear_cond_lock);
      pthread_mutex_unlock(&sl_dev->status_clear_cond_lock);
    }
  }
}

int _sl_ping(sl_device *sl_dev)
{
  const uint8_t cmd[2]={PING_CMD_ID, ~PING_CMD_ID};
  return serial_write(&sl_dev->sdev, cmd, 2);
}

int _sl_ping_out_of_phase(sl_device *sl_dev)
{
  const uint8_t cmd[3]={0, PING_CMD_ID, ~PING_CMD_ID};
  return serial_write(&sl_dev->sdev, cmd, 3);
}

void sl_close(sl_device *sl_dev)
{
  sl_dev->running_thread = false;
  pthread_join(sl_dev->read_thread, NULL);
  serial_close(&(sl_dev->sdev));
  pthread_mutex_destroy(&sl_dev->write_return_cond_lock);
  pthread_cond_destroy(&sl_dev->write_return_cond);
  pthread_mutex_destroy(&sl_dev->status_clear_cond_lock);
  pthread_cond_destroy(&sl_dev->status_clear_cond);
}

void *sl_read_thread(void *param)
{
  int ret;

  sl_device* sl_dev = (sl_device*) param;
  device* sdev = &sl_dev->sdev;
  bool volatile* running_thread = &sl_dev->running_thread;
#define SL_BUFSIZE (2*MAX_PACKET_SIZE-1)
  uint8_t buf[SL_BUFSIZE];
  uint8_t* bptr=buf;
  uint8_t* cmd_start=buf;
  int b;
  uint8_t cmd_nbytes;
  uint8_t check;
  int16_t req_cmd;
  uint16_t num_trials=0;

  while(*running_thread) {
    ret=serial_read(sdev, bptr, SL_BUFSIZE-(bptr-buf));

    if(ret==0) {

      //If waiting for command response
      if(__atomic_load_n(&sl_dev->req_cmd, __ATOMIC_SEQ_CST)>=0) {
	++num_trials;

	//If writing seems out of sync
	if(num_trials>SL_CMD_NUM_READ_TRIALS) {
	  fprintf(stderr,"%s: Warning: Writing out of sync!\n",__func__);
          pthread_mutex_lock(&sl_dev->write_return_cond_lock);
	  sl_dev->status|=SL_WRITE_OUT_OF_SYNC;
	  num_trials=0;
	  _sl_ping_out_of_phase(sl_dev);
          pthread_cond_signal(&sl_dev->write_return_cond);
          pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
	}
      }
      continue; 

    } else if(ret<0) {
      DEBUG_PRINT2("\nRead Error: %s", strerror(errno));
      break;
    }

    //Total number of bytes read
    ret+=bptr-buf; 
    //Last read byte
    bptr=buf+ret;
    //cmd_nbytes includes checksum, but not ID
    cmd_nbytes=DEV_CMD_NBYTES(*cmd_start)-1;

    //While it is possible that the read data contains the candidate command
    while(cmd_nbytes+1 <= bptr-cmd_start) {
      check=*cmd_start;

      for(b=1; b<cmd_nbytes; ++b) check+=cmd_start[b];
      check=~check;

      //If checksum matches, we assume sync is achieved
      if(check==cmd_start[cmd_nbytes]) {
	//Process packet here

	//If we just receive a syncing signal
	if((sl_dev->status&SL_READ_OUT_OF_SYNC) && cmd_start[0]==PING_CMD_ID) {
          pthread_mutex_lock(&sl_dev->write_return_cond_lock);
	  sl_dev->status = 0;
          pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
          pthread_mutex_lock(&sl_dev->status_clear_cond_lock);
	  pthread_cond_signal(&sl_dev->status_clear_cond);
          pthread_mutex_unlock(&sl_dev->status_clear_cond_lock);
	}
        pthread_mutex_lock(&sl_dev->write_return_cond_lock);
	req_cmd=__atomic_load_n(&sl_dev->req_cmd, __ATOMIC_SEQ_CST);

	//If the returned command is the requested command
	if(req_cmd>=0 && cmd_start[0]==req_cmd) {
	  memcpy((uint8_t*)&sl_dev->ret_cmd, cmd_start, cmd_nbytes+1);
          pthread_cond_signal(&sl_dev->write_return_cond);
	}
        pthread_mutex_unlock(&sl_dev->write_return_cond_lock);

	cmd_start+=cmd_nbytes+1;
	break;

	//Else we might be out of sync
      } else {

	if(!(sl_dev->status&SL_READ_OUT_OF_SYNC)) {
	  fprintf(stderr,"%s: Warning: Read out of sync!\n",__func__);
          pthread_mutex_lock(&sl_dev->write_return_cond_lock);
	  sl_dev->status|=SL_READ_OUT_OF_SYNC;
	  num_trials=0;
	  _sl_ping(sl_dev);
          pthread_cond_signal(&sl_dev->write_return_cond);
          pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
	}
	++cmd_start;
	assert(cmd_start<=bptr);
	cmd_nbytes=DEV_CMD_NBYTES(*cmd_start)-1;
      }
    }
    memmove(buf, cmd_start, bptr-cmd_start+1);
    cmd_start=bptr=buf;
  }
  return NULL;
}
