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
    if(rr.resp.bytes[0] != rr.req.id) return -(int)INT8_MAX;\
    if(rr.resp.bytes[1] != 0) return (int8_t)rr.resp.bytes[1];\
})

static inline int send_receive_ping_cmd(void){struct req_resp rr={{PING_CMD_ID},{PING_CMD_ID}}; return send_recv_cmd(&gGlobals.sl_dev, &rr);}
static inline int send_receive_reset_cmd(void){struct req_resp rr={{RESET_CMD_ID},{RESET_CMD_ID}}; return send_recv_cmd(&gGlobals.sl_dev, &rr);}

static inline int send_receive_eeprom_save_cmd(void){struct req_resp rr={{EEPROM_SAVE_CMD_REQ_ID},{ACK_CMD_ID}}; int ret=send_recv_cmd(&gGlobals.sl_dev, &rr); if(ret) return ret; CHECK_ACK_REPLY(rr); return 0;}

int send_receive_get_lm75a_temp_sensor_list_cmd(uint8_t* const list);
int send_receive_add_lm75a_temp_sensor_cmd(const uint8_t id);
int send_receive_del_lm75a_temp_sensor_cmd(const uint8_t id);
int send_receive_get_analog_temp_sensor_list_cmd(uint8_t* const list);
int send_receive_add_analog_temp_sensor_cmd(const uint8_t id);
int send_receive_del_analog_temp_sensor_cmd(const uint8_t id);
int send_receive_get_lm75a_sensor_value_cmd(const uint8_t id, int16_t* const value);
int send_receive_get_analog_sensor_value_cmd(const uint8_t id, int16_t* const value);
int send_receive_get_soft_sensor_value_cmd(const uint8_t id, int16_t* const value);
int send_receive_get_lm75a_temp_sensor_calib_cmd(const uint8_t id, int16_t* a0, int16_t* a1, int16_t* a2);
int send_receive_get_analog_temp_sensor_calib_cmd(const uint8_t id, int16_t* a0, int16_t* a1, int16_t* a2);
int send_receive_set_lm75a_temp_sensor_calib_cmd(const uint8_t id, const int16_t a0, const int16_t a1, const int16_t a2);
int send_receive_set_analog_temp_sensor_calib_cmd(const uint8_t id, const int16_t a0, const int16_t a1, const int16_t a2);
int send_receive_set_soft_temp_sensor_value_cmd(const uint8_t id, const int16_t value);

int send_receive_get_fan_list_cmd(uint8_t* const list);
int send_receive_add_fan_cmd(const uint8_t id);
int send_receive_del_fan_cmd(const uint8_t id);
int send_receive_get_fan_lm75a_temp_sensor_list_cmd(const uint8_t fan_id, uint8_t* const list);
int send_receive_get_fan_analog_temp_sensor_list_cmd(const uint8_t fan_id, uint8_t* const list);
int send_receive_get_fan_soft_temp_sensor_list_cmd(const uint8_t fan_id, uint8_t* const list);
int send_receive_add_fan_lm75a_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id);
int send_receive_add_fan_analog_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id);
int send_receive_add_fan_soft_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id);
int send_receive_del_fan_lm75a_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id);
int send_receive_del_fan_analog_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id);
int send_receive_del_fan_soft_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id);
int send_receive_add_fan_curve_point_cmd(const uint8_t fan_id, const int8_t temp, const uint8_t output);
int send_receive_del_fan_curve_point_cmd(const uint8_t fan_id, const uint8_t index);
int send_receive_get_fan_n_curve_points_cmd(const uint8_t fan_id, uint8_t* const ncurvepoints);

int send_receive_get_fan_rpm_cmd(const uint8_t id, int16_t* const rpm);

int send_receive_get_fan_mode_cmd(const uint8_t id, uint8_t* const mode);
int send_receive_switch_fan_control_cmd(const uint8_t id, const uint8_t mode);
int send_receive_get_fan_adc_value_cmd(const uint8_t id, int16_t* const adc_value);
int send_receive_get_fan_output_cmd(const uint8_t id, uint8_t* const output);
int send_receive_set_fan_output_cmd(const uint8_t id, const uint8_t output);
int send_receive_set_fan_output_auto_cmd(const uint8_t id, const uint8_t output);
int send_receive_get_fan_duty_cycle_response_cmd(const uint8_t id, uint16_t* const dc_no_out, int16_t* const ddcdout, int16_t* const d2dcdout2);
int send_receive_set_fan_duty_cycle_response_cmd(const uint8_t id, const uint16_t dc_no_out, const int16_t ddcdout);
int send_receive_get_fan_voltage_response_cmd(const uint8_t id, uint16_t* const v_no_out, int16_t* const dvdout, int16_t* const d2vdout2);
int send_receive_set_fan_voltage_response_cmd(const uint8_t id, const uint16_t v_no_out, const int16_t dvdout);
int send_receive_get_fan_mode_transitions_cmd(const uint8_t id, uint8_t* const pwm_to_voltage_output, uint8_t* const voltage_to_pwm_output);
int send_receive_set_fan_mode_transitions_cmd(const uint8_t id, const uint8_t pwm_to_voltage_output, const uint8_t voltage_to_pwm_output);

int calibrate_fan_voltage_response_cmd(const uint8_t id, const uint16_t min_voltage);
int calibrate_fan_duty_cycle_response_cmd(const uint8_t id, const uint8_t min_duty_cycle);
int _get_stable_fan_rpm(const uint8_t id, const uint16_t noscillations, double* const average_rpm);
int _get_fan_rpm(const uint8_t id, const int16_t prev_rpm, int16_t* const rpm);

#endif
