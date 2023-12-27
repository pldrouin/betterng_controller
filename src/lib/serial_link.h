#ifndef _SERIAL_LINK_
#define _SERIAL_LINK_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

#include <math.h>

#include "utils.h"
#include "serial.h"
#include "cmd_common.h"

#define DEFAULT_NUM_TRIALS 16
#define CMD_TIMEOUT(CMD) ((uint16_t)ceil(((float)CMD ## _CMD_US_TIMEOUT)/SERIAL_READ_US_TIMEOUT))

//#define BUILD_ONE_BYTE_CMD(cmd, ID) ({(cmd)->id=ID; calc_check_one_byte(cmd);})
//#define BUILD_TWO_BYTES_CMD(cmd, ID, value) ({(cmd)->id=ID; (cmd)->byte1=value; calc_check_two_bytes(cmd);})
//#define BUILD_THREE_BYTES_CMD(cmd, ID, value1, value2) ({(cmd)->id=ID; (cmd)->byte1=value1; (cmd)->byte2=value2; calc_check_three_bytes(cmd);})

//#define send_one_byte_cmd(sl_dev, ID, cmd) ({BUILD_ONE_BYTE_CMD(cmd, ID); _sl_write_cmd(sl_dev, cmd, 2, NULL);})
//#define send_two_bytes_cmd(sl_dev, ID, value, cmd) ({BUILD_TWO_BYTES_CMD(cmd, ID, value); _sl_write_cmd(sl_dev, cmd, 3, NULL);})
//#define send_three_bytes_cmd(sl_dev, ID, value1, value2, cmd) ({BUILD_THREE_BYTES_CMD(cmd, ID, value1, value2); _sl_write_cmd(sl_dev, cmd, 4, NULL);})
#define send_cmd(sl_dev, cmd) ({calc_check_bytes(cmd); _sl_write_cmd(sl_dev, cmd, cmd->nbytes+2, NULL);})

//#define send_recv_one_byte_cmd(sl_dev, ID, resp_ID, req_resp) ({BUILD_ONE_BYTE_CMD(&(req_resp)->req, ID); (req_resp)->resp.id=resp_ID; _sl_write_cmd(sl_dev, &(req_resp)->req, 2, &(req_resp)->resp);})
//#define send_recv_two_bytes_cmd(sl_dev, ID, value, resp_ID, req_resp) ({BUILD_TWO_BYTES_CMD(&(req_resp)->req, ID, value); (req_resp)->resp.id=resp_ID; _sl_write_cmd(sl_dev, &(req_resp)->req, 3, &(req_resp)->resp);})
//#define send_recv_three_bytes_cmd(sl_dev, ID, value1, value2, resp_ID, req_resp) ({BUILD_THREE_BYTES_CMD(&(req_resp)->req, ID, value1, value2); (req_resp)->resp.id=resp_ID; _sl_write_cmd(sl_dev, &(req_resp)->req, 4, &(req_resp)->resp);})
#define send_recv_cmd(sl_dev, req_resp) ({calc_check_bytes(&(req_resp)->req); _sl_write_cmd(sl_dev, &(req_resp)->req, (req_resp)->req.nbytes+2, &(req_resp)->resp);})

enum {SL_READ_OUT_OF_SYNC=1, SL_WRITE_OUT_OF_SYNC=2, SL_RECOVERED_SYNC=3};

/**
 * This struct holds the thread identifiers, thread flag, queue variable and serial device struct
 **/
typedef struct
{
    device sdev;
    volatile bool running_thread;
    uint8_t status;
    volatile int16_t req_cmd;
    volatile struct cmd ret_cmd;
    pthread_t read_thread;
    pthread_cond_t write_return_cond;
    pthread_mutex_t write_return_cond_lock;
} sl_device;

struct req_resp{
  struct cmd req;
  struct cmd resp;
};

struct cmd_info{
  uint16_t timeout;
  uint8_t resp_nbytes;
};

void sl_init(sl_device *sl_dev);

int sl_start(sl_device *sl_dev, const char *serial_port, const uint32_t baud_rate);

int _sl_write_cmd(sl_device *sl_dev, const struct cmd* sent_cmd, const uint8_t sent_cmd_nbytes, struct cmd* ret_cmd);

int _sl_ping(sl_device *sl_dev);
int _sl_ping_out_of_phase(sl_device *sl_dev);

void sl_close(sl_device *sl_dev);

void *sl_read_thread(void *param);

#endif

