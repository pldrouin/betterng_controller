#ifndef _CONTROLLER_CMD_
#define _CONTROLLER_CMD_

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include "serial_link.h"

#define CHECK_FAN_ID(id) ({\
  if(id>3) {\
    fprintf(stderr,"%s: Error: Fan id %u is invalid!\n",__func__,id);\
    return -1;\
  }\
})


#define CHECK_ACK_REPLY(rr) ({\
    if(rr.resp.bytes[0] != rr.req.id) return -2;\
    if(rr.resp.bytes[1] != 0) return -3;\
})

static inline int send_receive_ping_cmd(sl_device *sl_dev){struct req_resp rr={{PING_CMD_ID},{PING_CMD_ID}}; return send_recv_cmd(sl_dev, &rr);}
static inline int send_receive_reset_cmd(sl_device *sl_dev){struct req_resp rr={{RESET_CMD_ID},{RESET_CMD_ID}}; return send_recv_cmd(sl_dev, &rr);}

int send_receive_get_fan_rpm_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* rpm);
int send_receive_get_fan_voltage_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* voltage);
int send_receive_get_fan_voltage_target_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* voltage);
int send_receive_fan_adc_calibration_cmd(sl_device *sl_dev, const uint8_t id);

int send_receive_switch_fan_control_cmd(sl_device *sl_dev, const uint8_t id, const uint8_t mode);
int send_receive_get_fan_output_cmd(sl_device *sl_dev, const uint8_t id, uint8_t* output);
int send_receive_set_fan_output_cmd(sl_device *sl_dev, const uint8_t id, const uint8_t output);
int send_receive_get_fan_voltage_response_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* v_no_out, uint16_t* dvdout, int16_t* d2vdout2);
int send_receive_set_fan_voltage_response_cmd(sl_device *sl_dev, const uint8_t id, const uint16_t vnoout, const uint16_t dvdout);

#endif
