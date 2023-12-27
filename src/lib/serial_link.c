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

const struct cmd_info cmd_info[] = {
  {CMD_TIMEOUT(DEFAULT), 0}, // PING 0
  {CMD_TIMEOUT(DEFAULT), 0}, // RESET 1
  {CMD_TIMEOUT(EEPROM_SAVE), 0}, // EEPROM_SAVE 2
  {CMD_TIMEOUT(DEFAULT), 0}, // EEPROM_SAVE 3
  {CMD_TIMEOUT(DEFAULT), 0}, //  4
  {CMD_TIMEOUT(DEFAULT), 0}, //  5
  {CMD_TIMEOUT(DEFAULT), 0}, //  6
  {CMD_TIMEOUT(DEFAULT), 0}, //  7
  {CMD_TIMEOUT(DEFAULT), 0}, //  8
  {CMD_TIMEOUT(DEFAULT), 0}, //  9
  {CMD_TIMEOUT(DEFAULT), 0}, // 10
  {CMD_TIMEOUT(DEFAULT), 0}, // 11
  {CMD_TIMEOUT(DEFAULT), 0}, // 12
  {CMD_TIMEOUT(DEFAULT), 0}, // 13
  {CMD_TIMEOUT(DEFAULT), 0}, // 14
  {CMD_TIMEOUT(DEFAULT), 0}, // 15
  {CMD_TIMEOUT(DEFAULT), 0}, // 16
  {CMD_TIMEOUT(DEFAULT), 0}, // 17
  {CMD_TIMEOUT(DEFAULT), 0}, // 18
  {CMD_TIMEOUT(DEFAULT), 0}, // 19
  {CMD_TIMEOUT(DEFAULT), 0}, // 20
  {CMD_TIMEOUT(DEFAULT), 0}, // 21
  {CMD_TIMEOUT(DEFAULT), 0}, // 22
  {CMD_TIMEOUT(DEFAULT), 0}, // 23
  {CMD_TIMEOUT(DEFAULT), 0}, // 24
  {CMD_TIMEOUT(DEFAULT), 0}, // 25
  {CMD_TIMEOUT(DEFAULT), 0}, // 26
  {CMD_TIMEOUT(DEFAULT), 0}, // 27
  {CMD_TIMEOUT(DEFAULT), 0}, // 28
  {CMD_TIMEOUT(DEFAULT), 0}, // 29
  {CMD_TIMEOUT(DEFAULT), 0}, // 30
  {CMD_TIMEOUT(DEFAULT), 0}, // 31
  {CMD_TIMEOUT(DEFAULT), 0}, // 32
  {CMD_TIMEOUT(DEFAULT), 0}, // 33
  {CMD_TIMEOUT(DEFAULT), 0}, // 34
  {CMD_TIMEOUT(DEFAULT), 0}, // 35
  {CMD_TIMEOUT(DEFAULT), 0}, // 36
  {CMD_TIMEOUT(DEFAULT), 0}, // 37
  {CMD_TIMEOUT(DEFAULT), 0}, // 38
  {CMD_TIMEOUT(DEFAULT), 0}, // 39
  {CMD_TIMEOUT(DEFAULT), 0}, // 40
  {CMD_TIMEOUT(DEFAULT), 0}, // 41
  {CMD_TIMEOUT(DEFAULT), 0}, // 42
  {CMD_TIMEOUT(DEFAULT), 0}, // 43
  {CMD_TIMEOUT(DEFAULT), 0}, // 44
  {CMD_TIMEOUT(DEFAULT), 0}, // 45
  {CMD_TIMEOUT(DEFAULT), 0}, // 46
  {CMD_TIMEOUT(DEFAULT), 0}, // 47
  {CMD_TIMEOUT(DEFAULT), 0}, // 48
  {CMD_TIMEOUT(DEFAULT), 0}, // 49
  {CMD_TIMEOUT(DEFAULT), 0}, // 50
  {CMD_TIMEOUT(DEFAULT), 0}, // 51
  {CMD_TIMEOUT(DEFAULT), 0}, // 52
  {CMD_TIMEOUT(DEFAULT), 0}, // 53
  {CMD_TIMEOUT(DEFAULT), 0}, // 54
  {CMD_TIMEOUT(DEFAULT), 0}, // 55
  {CMD_TIMEOUT(DEFAULT), 0}, // 56
  {CMD_TIMEOUT(DEFAULT), 0}, // 57
  {CMD_TIMEOUT(DEFAULT), 0}, // 58
  {CMD_TIMEOUT(DEFAULT), 0}, // 59
  {CMD_TIMEOUT(DEFAULT), 0}, // 60
  {CMD_TIMEOUT(DEFAULT), 0}, // 61
  {CMD_TIMEOUT(DEFAULT), 0}, // 62
  {CMD_TIMEOUT(DEFAULT), 0}, // 63
  {CMD_TIMEOUT(DEFAULT), 0}, // 64
  {CMD_TIMEOUT(DEFAULT), 0}, // 65
  {CMD_TIMEOUT(DEFAULT), 0}, // 66
  {CMD_TIMEOUT(DEFAULT), 0}, // 67
  {CMD_TIMEOUT(DEFAULT), 0}, // 68
  {CMD_TIMEOUT(DEFAULT), 0}, // 69
  {CMD_TIMEOUT(DEFAULT), 0}, // 70
  {CMD_TIMEOUT(DEFAULT), 0}, // 71
  {CMD_TIMEOUT(DEFAULT), 0}, // 72
  {CMD_TIMEOUT(DEFAULT), 0}, // 73
  {CMD_TIMEOUT(DEFAULT), 0}, // 74
  {CMD_TIMEOUT(DEFAULT), 0}, // 75
  {CMD_TIMEOUT(DEFAULT), 0}, // 76
  {CMD_TIMEOUT(DEFAULT), 0}, // 77
  {CMD_TIMEOUT(DEFAULT), 0}, // 78
  {CMD_TIMEOUT(DEFAULT), 0}, // 79
  {CMD_TIMEOUT(DEFAULT), 0}, // 80
  {CMD_TIMEOUT(DEFAULT), 0}, // 81
  {CMD_TIMEOUT(DEFAULT), 0}, // 82
  {CMD_TIMEOUT(DEFAULT), 0}, // 83
  {CMD_TIMEOUT(DEFAULT), 0}, // 84
  {CMD_TIMEOUT(DEFAULT), 0}, // 85
  {CMD_TIMEOUT(DEFAULT), 0}, // 86
  {CMD_TIMEOUT(DEFAULT), 0}, // 87
  {CMD_TIMEOUT(DEFAULT), 0}, // 88
  {CMD_TIMEOUT(DEFAULT), 0}, // 89
  {CMD_TIMEOUT(DEFAULT), 0}, // 90
  {CMD_TIMEOUT(DEFAULT), 0}, // 91
  {CMD_TIMEOUT(DEFAULT), 0}, // 92
  {CMD_TIMEOUT(DEFAULT), 0}, // 93
  {CMD_TIMEOUT(DEFAULT), 0}, // 94
  {CMD_TIMEOUT(DEFAULT), 0}, // 95
  {CMD_TIMEOUT(DEFAULT), 0}, // 96
  {CMD_TIMEOUT(DEFAULT), 0}, // 97
  {CMD_TIMEOUT(DEFAULT), 0}, // 98
  {CMD_TIMEOUT(DEFAULT), 0}, // 99
  {CMD_TIMEOUT(DEFAULT), 0}, //100
  {CMD_TIMEOUT(DEFAULT), 0}, //101
  {CMD_TIMEOUT(DEFAULT), 0}, //102
  {CMD_TIMEOUT(DEFAULT), 0}, //103
  {CMD_TIMEOUT(DEFAULT), 0}, //104
  {CMD_TIMEOUT(DEFAULT), 0}, //105
  {CMD_TIMEOUT(DEFAULT), 0}, //106
  {CMD_TIMEOUT(DEFAULT), 0}, //107
  {CMD_TIMEOUT(DEFAULT), 0}, //108
  {CMD_TIMEOUT(DEFAULT), 0}, //109
  {CMD_TIMEOUT(DEFAULT), 0}, //110
  {CMD_TIMEOUT(DEFAULT), 0}, //111
  {CMD_TIMEOUT(DEFAULT), 0}, //112
  {CMD_TIMEOUT(DEFAULT), 0}, //113
  {CMD_TIMEOUT(DEFAULT), 0}, //114
  {CMD_TIMEOUT(DEFAULT), 0}, //115
  {CMD_TIMEOUT(DEFAULT), 0}, //116
  {CMD_TIMEOUT(DEFAULT), 0}, //117
  {CMD_TIMEOUT(DEFAULT), 0}, //118
  {CMD_TIMEOUT(DEFAULT), 0}, //119
  {CMD_TIMEOUT(DEFAULT), 0}, //120
  {CMD_TIMEOUT(DEFAULT), 0}, //121
  {CMD_TIMEOUT(DEFAULT), 0}, //122
  {CMD_TIMEOUT(DEFAULT), 0}, //123
  {CMD_TIMEOUT(DEFAULT), 0}, //124
  {CMD_TIMEOUT(DEFAULT), 0}, //125
  {CMD_TIMEOUT(DEFAULT), 0}, //126
  {CMD_TIMEOUT(DEFAULT), 0}, //127
  {CMD_TIMEOUT(DEFAULT), 0}, //128
  {CMD_TIMEOUT(DEFAULT), 0}, //129
  {CMD_TIMEOUT(DEFAULT), 0}, //130
  {CMD_TIMEOUT(DEFAULT), 0}, //131
  {CMD_TIMEOUT(DEFAULT), 0}, //132
  {CMD_TIMEOUT(DEFAULT), 0}, //133
  {CMD_TIMEOUT(DEFAULT), 0}, //134
  {CMD_TIMEOUT(DEFAULT), 0}, //135
  {CMD_TIMEOUT(DEFAULT), 0}, //136
  {CMD_TIMEOUT(DEFAULT), 0}, //137
  {CMD_TIMEOUT(DEFAULT), 0}, //138
  {CMD_TIMEOUT(DEFAULT), 0}, //139
  {CMD_TIMEOUT(DEFAULT), 0}, //140
  {CMD_TIMEOUT(DEFAULT), 0}, //141
  {CMD_TIMEOUT(DEFAULT), 0}, //142
  {CMD_TIMEOUT(DEFAULT), 0}, //143
  {CMD_TIMEOUT(DEFAULT), 0}, //144
  {CMD_TIMEOUT(DEFAULT), 0}, //145
  {CMD_TIMEOUT(DEFAULT), 0}, //146
  {CMD_TIMEOUT(DEFAULT), 0}, //147
  {CMD_TIMEOUT(DEFAULT), 0}, //148
  {CMD_TIMEOUT(DEFAULT), 0}, //149
  {CMD_TIMEOUT(DEFAULT), 0}, //150
  {CMD_TIMEOUT(DEFAULT), 0}, //151
  {CMD_TIMEOUT(DEFAULT), 0}, //152
  {CMD_TIMEOUT(DEFAULT), 0}, //153
  {CMD_TIMEOUT(DEFAULT), 0}, //154
  {CMD_TIMEOUT(DEFAULT), 0}, //155
  {CMD_TIMEOUT(DEFAULT), 0}, //156
  {CMD_TIMEOUT(DEFAULT), 0}, //157
  {CMD_TIMEOUT(DEFAULT), 0}, //158
  {CMD_TIMEOUT(DEFAULT), 0}, //159
  {CMD_TIMEOUT(DEFAULT), 0}, //160
  {CMD_TIMEOUT(DEFAULT), 0}, //161
  {CMD_TIMEOUT(DEFAULT), 0}, //162
  {CMD_TIMEOUT(DEFAULT), 0}, //163
  {CMD_TIMEOUT(DEFAULT), 0}, //164
  {CMD_TIMEOUT(DEFAULT), 0}, //165
  {CMD_TIMEOUT(DEFAULT), 0}, //166
  {CMD_TIMEOUT(DEFAULT), 0}, //167
  {CMD_TIMEOUT(DEFAULT), 0}, //168
  {CMD_TIMEOUT(DEFAULT), 0}, //169
  {CMD_TIMEOUT(DEFAULT), 0}, //170
  {CMD_TIMEOUT(DEFAULT), 0}, //171
  {CMD_TIMEOUT(DEFAULT), 0}, //172
  {CMD_TIMEOUT(DEFAULT), 0}, //173
  {CMD_TIMEOUT(DEFAULT), 0}, //174
  {CMD_TIMEOUT(DEFAULT), 0}, //175
  {CMD_TIMEOUT(DEFAULT), 0}, //176
  {CMD_TIMEOUT(DEFAULT), 0}, //177
  {CMD_TIMEOUT(DEFAULT), 0}, //178
  {CMD_TIMEOUT(DEFAULT), 0}, //179
  {CMD_TIMEOUT(DEFAULT), 0}, //180
  {CMD_TIMEOUT(DEFAULT), 0}, //181
  {CMD_TIMEOUT(DEFAULT), 0}, //182
  {CMD_TIMEOUT(DEFAULT), 0}, //183
  {CMD_TIMEOUT(DEFAULT), 0}, //184
  {CMD_TIMEOUT(DEFAULT), 0}, //185
  {CMD_TIMEOUT(DEFAULT), 0}, //186
  {CMD_TIMEOUT(DEFAULT), 0}, //187
  {CMD_TIMEOUT(DEFAULT), 0}, //188
  {CMD_TIMEOUT(DEFAULT), 0}, //189
  {CMD_TIMEOUT(DEFAULT), 0}, //190
  {CMD_TIMEOUT(DEFAULT), 0}, //191
  {CMD_TIMEOUT(DEFAULT), 0}, //192
  {CMD_TIMEOUT(DEFAULT), 0}, //193
  {CMD_TIMEOUT(DEFAULT), 0}, //194
  {CMD_TIMEOUT(DEFAULT), 0}, //195
  {CMD_TIMEOUT(DEFAULT), 0}, //196
  {CMD_TIMEOUT(DEFAULT), 0}, //197
  {CMD_TIMEOUT(DEFAULT), 0}, //198
  {CMD_TIMEOUT(DEFAULT), 0}, //199
  {CMD_TIMEOUT(DEFAULT), 0}, //200
  {CMD_TIMEOUT(DEFAULT), 0}, //201
  {CMD_TIMEOUT(DEFAULT), 0}, //202
  {CMD_TIMEOUT(DEFAULT), 0}, //203
  {CMD_TIMEOUT(DEFAULT), 0}, //204
  {CMD_TIMEOUT(DEFAULT), 0}, //205
  {CMD_TIMEOUT(DEFAULT), 0}, //206
  {CMD_TIMEOUT(DEFAULT), 0}, //207
  {CMD_TIMEOUT(DEFAULT), 0}, //208
  {CMD_TIMEOUT(DEFAULT), 0}, //209
  {CMD_TIMEOUT(DEFAULT), 0}, //210
  {CMD_TIMEOUT(DEFAULT), 0}, //211
  {CMD_TIMEOUT(DEFAULT), 0}, //212
  {CMD_TIMEOUT(DEFAULT), 0}, //213
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_LM75A_TEMP_SENSOR_LIST_CMD_RESP_ID 214
  {CMD_TIMEOUT(DEFAULT), 0}, // 215
  {CMD_TIMEOUT(DEFAULT), 0}, // 216
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_ANALOG_TEMP_SENSOR_LIST_CMD_RESP_ID 217
  {CMD_TIMEOUT(DEFAULT), 2}, // GET_LM75A_SENSOR_VALUE_CMD_RESP_ID 218
  {CMD_TIMEOUT(DEFAULT), 2}, // GET_ANALOG_SENSOR_VALUE_CMD_RESP_ID 219
  {CMD_TIMEOUT(DEFAULT), 2}, // GET_SOFT_SENSOR_VALUE_CMD_RESP_ID 220
  {CMD_TIMEOUT(DEFAULT), 7}, // GET_LM75A_TEMP_SENSOR_CALIB_CMD_RESP_ID 221
  {CMD_TIMEOUT(DEFAULT), 7}, // GET_ANALOG_TEMP_SENSOR_CALIB_CMD_RESP_ID 222
  {CMD_TIMEOUT(DEFAULT), 0}, // 223
  {CMD_TIMEOUT(DEFAULT), 0}, // 224
  {CMD_TIMEOUT(DEFAULT), 0}, // 225
  {CMD_TIMEOUT(DEFAULT), 0}, // 226
  {CMD_TIMEOUT(DEFAULT), 0}, // 227
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_LIST_CMD_RESP_ID 228
  {CMD_TIMEOUT(DEFAULT), 0}, // 229
  {CMD_TIMEOUT(DEFAULT), 0}, // 230
  {CMD_TIMEOUT(DEFAULT), 0}, // 231
  {CMD_TIMEOUT(DEFAULT), 0}, // 232
  {CMD_TIMEOUT(DEFAULT), 0}, // 233
  {CMD_TIMEOUT(DEFAULT), 0}, // 234
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_LM75A_TEMP_SENSOR_LIST_CMD_RESP_ID 235
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_ANALOG_TEMP_SENSOR_LIST_CMD_RESP_ID 236
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_SOFT_TEMP_SENSOR_LIST_CMD_RESP_ID 237
  {CMD_TIMEOUT(DEFAULT), 0}, // 238
  {CMD_TIMEOUT(DEFAULT), 0}, // 239
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_N_CURVE_POINTS_CMD_RESP_ID 240
  {CMD_TIMEOUT(DEFAULT), 3}, // GET_FAN_CURVE_POINT_CMD_RESP_ID 241
  {CMD_TIMEOUT(DEFAULT), 2}, // GET_FAN_RPM_CMD_RESP 242
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_OUTPUT_RESPONSE 243
  {CMD_TIMEOUT(DEFAULT), 0}, //244
  {CMD_TIMEOUT(DEFAULT), 2}, // GET_FAN_ADC_VALUE_RESPONSE 245
  {CMD_TIMEOUT(DEFAULT), 1}, // GET_FAN_OUTPUT_RESPONSE 246
  {CMD_TIMEOUT(DEFAULT), 0}, //247
  {CMD_TIMEOUT(DEFAULT), 0}, //248
  {CMD_TIMEOUT(DEFAULT), 6}, // GET_FAN_DUTY_CYCLE_RESPONSE 249
  {CMD_TIMEOUT(DEFAULT), 0}, //250
  {CMD_TIMEOUT(DEFAULT), 6}, // GET_FAN_VOLTAGE_RESPONSE 251
  {CMD_TIMEOUT(DEFAULT), 0}, //252
  {CMD_TIMEOUT(DEFAULT), 2}, // GET_FAN_MODE_TRANSITIONS 253
  {CMD_TIMEOUT(DEFAULT), 0}, //254
  {CMD_TIMEOUT(DEFAULT), 2}, // ACK 255
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
      if((req_cmd=__atomic_load_n(&sl_dev->req_cmd, __ATOMIC_SEQ_CST))>=0) {
	++num_trials;

	//If writing seems out of sync
	if(num_trials>cmd_info[req_cmd].timeout) {
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
    cmd_nbytes=cmd_info[*cmd_start].resp_nbytes+1;

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
	cmd_nbytes=cmd_info[*cmd_start].resp_nbytes+1;
      }
    }
    DEBUG_PRINT2("Copy %li bytes from %p to %p. bptr is %p\n",bptr-cmd_start, cmd_start, buf, bptr);
    memmove(buf, cmd_start, bptr-cmd_start);
    bptr=buf+(bptr-cmd_start);
    cmd_start=buf;
  }
  return NULL;
}
