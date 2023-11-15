#ifndef _CONTROLLER_CMD_
#define _CONTROLLER_CMD_

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include "serial_link.h"
#include "globals.h"

#define RPM_READING_N_OSCILLATIONS (10)

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

static inline int send_receive_ping_cmd(void){struct req_resp rr={{PING_CMD_ID},{PING_CMD_ID}}; return send_recv_cmd(&gGlobals.sl_dev, &rr);}
static inline int send_receive_reset_cmd(void){struct req_resp rr={{RESET_CMD_ID},{RESET_CMD_ID}}; return send_recv_cmd(&gGlobals.sl_dev, &rr);}

int send_receive_get_fan_rpm_cmd(const uint8_t id, uint16_t* rpm);
int send_receive_get_fan_off_level_cmd(const uint8_t id, int16_t* off_level);
int send_receive_get_fan_voltage_cmd(const uint8_t id, uint16_t* voltage);
int send_receive_get_fan_voltage_target_cmd(const uint8_t id, uint16_t* voltage);
int send_receive_fan_adc_calibration_cmd(const uint8_t id);

int send_receive_switch_fan_control_cmd(const uint8_t id, const uint8_t mode);
int send_receive_get_fan_output_cmd(const uint8_t id, uint8_t* output);
int send_receive_set_fan_output_cmd(const uint8_t id, const uint8_t output);
int send_receive_get_fan_voltage_response_cmd(const uint8_t id, uint16_t* v_no_out, int16_t* dvdout, int16_t* d2vdout2);
int send_receive_set_fan_voltage_response_cmd(const uint8_t id, const uint16_t vnoout, const int16_t dvdout);

int calibrate_fan_voltage_response_cmd(const uint8_t id, const uint16_t min_voltage);
int _get_stable_fan_rpm(const uint8_t id, const uint16_t noscillations, double* average_rpm);
int _get_fan_rpm(const uint8_t id, const uint16_t prev_rpm, uint16_t* rpm);

#endif
