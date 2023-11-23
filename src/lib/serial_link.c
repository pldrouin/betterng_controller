#include<assert.h>

#include "serial_link.h"

///enable this to print debug data
//#define DEBUG_PRINT printf
//#define printtime printtime
#define DEBUG_PRINT(...)
#define printtime(...)
//#define DEBUG_PRINT2 printf
#define DEBUG_PRINT2(...)
//#define pthread_mutex_lock(x) {printf("%s: pthread_mutex_lock(%s) at ",__func__, #x); printtime(); pthread_mutex_lock(x);}
//#define pthread_mutex_unlock(x) {printf("%s: pthread_mutex_unlock(%s) at ",__func__, #x); printtime(); pthread_mutex_unlock(x);}
//#define pthread_cond_signal(x) {printf("%s: pthread_cond_signal(%s) at ",__func__, #x); printtime(); pthread_cond_signal(x);}
//#define pthread_cond_wait(x, xl) {printf("%s: pthread_cond_wait(%s, %s) at ",__func__, #x, #xl); printtime(); pthread_cond_wait(x, xl);}

const uint8_t input_cmd_nbytes[] = {
  0, // PING 0
  0, // RESET 1
  0, //  2
  0, //  3
  0, //  4
  0, //  5
  0, //  6
  0, //  7
  0, //  8
  0, //  9
  0, // 10
  0, // 11
  0, // 12
  0, // 13
  0, // 14
  0, // 15
  0, // 16
  0, // 17
  0, // 18
  0, // 19
  0, // 20
  0, // 21
  0, // 22
  0, // 23
  0, // 24
  0, // 25
  0, // 26
  0, // 27
  0, // 28
  0, // 29
  0, // 30
  0, // 31
  0, // 32
  0, // 33
  0, // 34
  0, // 35
  0, // 36
  0, // 37
  0, // 38
  0, // 39
  0, // 40
  0, // 41
  0, // 42
  0, // 43
  0, // 44
  0, // 45
  0, // 46
  0, // 47
  0, // 48
  0, // 49
  0, // 50
  0, // 51
  0, // 52
  0, // 53
  0, // 54
  0, // 55
  0, // 56
  0, // 57
  0, // 58
  0, // 59
  0, // 60
  0, // 61
  0, // 62
  0, // 63
  0, // 64
  0, // 65
  0, // 66
  0, // 67
  0, // 68
  0, // 69
  0, // 70
  0, // 71
  0, // 72
  0, // 73
  0, // 74
  0, // 75
  0, // 76
  0, // 77
  0, // 78
  0, // 79
  0, // 80
  0, // 81
  0, // 82
  0, // 83
  0, // 84
  0, // 85
  0, // 86
  0, // 87
  0, // 88
  0, // 89
  0, // 90
  0, // 91
  0, // 92
  0, // 93
  0, // 94
  0, // 95
  0, // 96
  0, // 97
  0, // 98
  0, // 99
  0, //100
  0, //101
  0, //102
  0, //103
  0, //104
  0, //105
  0, //106
  0, //107
  0, //108
  0, //109
  0, //110
  0, //111
  0, //112
  0, //113
  0, //114
  0, //115
  0, //116
  0, //117
  0, //118
  0, //119
  0, //120
  0, //121
  0, //122
  0, //123
  0, //124
  0, //125
  0, //126
  0, //127
  0, //128
  0, //129
  0, //130
  0, //131
  0, //132
  0, //133
  0, //134
  0, //135
  0, //136
  0, //137
  0, //138
  0, //139
  0, //140
  0, //141
  0, //142
  0, //143
  0, //144
  0, //145
  0, //146
  0, //147
  0, //148
  0, //149
  0, //150
  0, //151
  0, //152
  0, //153
  0, //154
  0, //155
  0, //156
  0, //157
  0, //158
  0, //159
  0, //160
  0, //161
  0, //162
  0, //163
  0, //164
  0, //165
  0, //166
  0, //167
  0, //168
  0, //169
  0, //170
  0, //171
  0, //172
  0, //173
  0, //174
  0, //175
  0, //176
  0, //177
  0, //178
  0, //179
  0, //180
  0, //181
  0, //182
  0, //183
  0, //184
  0, //185
  0, //186
  0, //187
  0, //188
  0, //189
  0, //190
  0, //191
  0, //192
  0, //193
  0, //194
  0, //195
  0, //196
  0, //197
  0, //198
  0, //199
  0, //200
  0, //201
  0, //202
  0, //203
  0, //204
  0, //205
  0, //206
  0, //207
  0, //208
  0, //209
  0, //210
  0, //211
  0, //212
  0, //213
  0, //214
  0, //215
  0, //216
  0, //217
  0, //218
  0, //219
  0, //220
  0, //221
  0, //222
  0, //223
  0, //224
  0, //225
  0, //226
  0, //227
  0, //228
  0, //229
  0, //230
  0, //231
  0, //232
  0, //233
  0, //234
  0, //235
  0, //236
  0, //237
  0, //238
  0, //239
  0, //240
  0, //241
  0, //242
  2, // GET_FAN_RPM_CMD_RESP 243
  2, // GET_FAN_OFF_LEVEL_CMD_RESP 244
  2, // GET_FAN_VOLTAGE_CMD_RESP 245
  2, // GET_FAN_VOLTAGE_TARGET_CMD_RESP 246
  0, //247
  0, //248
  1, // GET_FAN_OUTPUT_RESPONSE 249
  0, //250
  6, // GET_FAN_DUTY_CYCLE_RESPONSE 251
  0, //252
  6, // GET_FAN_VOLTAGE_RESPONSE 253
  0, //254
  2, // ACK 255
};

void sl_init(sl_device *sl_dev)
{
  sl_dev->status = 0;
  sl_dev->req_cmd = -1;
  pthread_mutex_init(&sl_dev->write_return_cond_lock, NULL);
  pthread_cond_init(&sl_dev->write_return_cond, NULL);
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

    ret=serial_write(&sl_dev->sdev, (uint8_t*)sent_cmd, sent_cmd_nbytes);

    if(ret!=sent_cmd_nbytes) {
      pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
      fprintf(stderr,"%s: Error: Wrote %u/%u bytes!\n",__func__,ret,sent_cmd_nbytes);
      return ret;

    } else {

      if(ret_cmd) __atomic_store_n(&sl_dev->req_cmd, ret_cmd->id, __ATOMIC_SEQ_CST);
      pthread_cond_wait(&sl_dev->write_return_cond, &sl_dev->write_return_cond_lock);
      assert(sl_dev->status==0 || sl_dev->status==SL_RECOVERED_SYNC);

      //If status recovered sync, we need to send the command again
      if(sl_dev->status==SL_RECOVERED_SYNC) {
	pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
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

    if(bptr+ret==buf) {

      //If waiting for command response
      if(__atomic_load_n(&sl_dev->req_cmd, __ATOMIC_SEQ_CST)>=0) {
	++num_trials;

	//If writing seems out of sync
	if(num_trials>SL_CMD_NUM_READ_TRIALS) {
	  fprintf(stderr,"%s: Warning: Writing out of sync!\n",__func__);
	  fprintf(stderr,"***********************************************************************************************\n");
	  sl_dev->status|=SL_WRITE_OUT_OF_SYNC;
	  num_trials=0;
	  _sl_ping(sl_dev);
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
    cmd_nbytes=input_cmd_nbytes[*cmd_start]+1;

    //While it is possible that the read data contains the candidate command
    while(cmd_nbytes+1 <= bptr-cmd_start) {
      check=*cmd_start;

      for(b=1; b<cmd_nbytes; ++b) check+=cmd_start[b];
      check=~check;
      DEBUG_PRINT2("cmd_nbytes is %u, check should be 0x%02x vs 0x%02x\n",cmd_nbytes,check,cmd_start[cmd_nbytes]);

      //If checksum matches, we assume sync is achieved
      if(check==cmd_start[cmd_nbytes]) {
	//Process packet here
        pthread_mutex_lock(&sl_dev->write_return_cond_lock);
	req_cmd=__atomic_load_n(&sl_dev->req_cmd, __ATOMIC_SEQ_CST);

	//If the returned command is the requested command
	if(req_cmd>=0 && cmd_start[0]==req_cmd) {
	  memcpy((uint8_t*)&sl_dev->ret_cmd, cmd_start, cmd_nbytes+1);
	  sl_dev->status = 0;
	  pthread_cond_signal(&sl_dev->write_return_cond);
          pthread_mutex_unlock(&sl_dev->write_return_cond_lock);

	  //Else if the returned command is not the requested command
	} else {

	  //If we just received a syncing signal
	  if((sl_dev->status&(SL_READ_OUT_OF_SYNC|SL_WRITE_OUT_OF_SYNC)) && cmd_start[0]==PING_CMD_ID) {
	    sl_dev->status = SL_RECOVERED_SYNC;
            pthread_cond_signal(&sl_dev->write_return_cond);
	    pthread_mutex_unlock(&sl_dev->write_return_cond_lock);

	  } else pthread_mutex_unlock(&sl_dev->write_return_cond_lock);
	}

	cmd_start+=cmd_nbytes+1;
	break;

	//Else we might be out of sync
      } else {

	if(!(sl_dev->status&SL_READ_OUT_OF_SYNC)) {
	  fprintf(stderr,"%s: Warning: Read out of sync!\n",__func__);
	  fprintf(stderr,"***********************************************************************************************\n");
	  sl_dev->status|=SL_READ_OUT_OF_SYNC;
	  num_trials=0;
	  _sl_ping(sl_dev);
	}
	++cmd_start;
	assert(cmd_start<=bptr);
	cmd_nbytes=input_cmd_nbytes[*cmd_start]+1;
      }
    }
    DEBUG_PRINT2("Copy %li bytes from %p to %p. bptr is %p\n",bptr-cmd_start, cmd_start, buf, bptr);
    memmove(buf, cmd_start, bptr-cmd_start);
    bptr=buf+(bptr-cmd_start);
    cmd_start=buf;
  }
  return NULL;
}
