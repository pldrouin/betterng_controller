#ifndef _CONTROLLER_CONFIG_
#define _CONTROLLER_CONFIG_

#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "globals.h"
#include "utils.h"
#include "args.h"
#include "ht.h"

#include "controller_cmd.h"

#define CONFIG_EXIT_RET (INT32_MAX)

int config();
void config_ht_populate();

int config_help(void);

int config_config(void);
int config_olog(void);
int config_elog(void);
int config_prompt(void);

int config_ping(void);
int config_reset(void);

#define CONFIG_GET_FAN_ID(id) ({\
  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf,PBUF_SIZE)<0) {\
    fprintf(stderr,"%s: Error: Missing fan ID!\n",__func__);\
    return -1;\
  }\
  sscanf(gGlobals.pbuf, "%" SCNu8, &id);\
})

#define CONFIG_GET_SENSOR_ID(id) ({\
  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf,PBUF_SIZE)<0) {\
    fprintf(stderr,"%s: Error: Missing sensor ID!\n",__func__);\
    return -1;\
  }\
  sscanf(gGlobals.pbuf, "%" SCNu8, &id);\
})

int config_eeprom_save(void);

int config_get_lm75a_temp_sensor_list(void);
int config_add_lm75a_temp_sensor(void);
int config_del_lm75a_temp_sensor(void);
int config_get_analog_temp_sensor_list(void);
int config_add_analog_temp_sensor(void);
int config_del_analog_temp_sensor(void);
int config_get_analog_temp_sensor_adc_value(void);
int config_get_lm75a_temp_sensor_value(void);
int config_get_analog_temp_sensor_value(void);
int config_get_soft_temp_sensor_value(void);
int config_get_lm75a_temp_sensor_calib(void);
int config_get_analog_temp_sensor_calib0(void);
int config_get_analog_temp_sensor_calib1(void);
int config_set_lm75a_temp_sensor_calib(void);
int config_set_analog_temp_sensor_calib0(void);
int config_set_analog_temp_sensor_calib1(void);
int config_set_soft_temp_sensor_value(void);
int config_get_lm75a_temp_sensor_alarm_value(void);
int config_get_analog_temp_sensor_alarm_value(void);
int config_get_soft_temp_sensor_alarm_value(void);
int config_set_lm75a_temp_sensor_alarm_value(void);
int config_set_analog_temp_sensor_alarm_value(void);
int config_set_soft_temp_sensor_alarm_value(void);

int config_get_fan_list(void);

int config_add_fan(void);
int config_del_fan(void);
int config_get_fan_lm75a_temp_sensor_list(void);
int config_get_fan_analog_temp_sensor_list(void);
int config_get_fan_soft_temp_sensor_list(void);
int config_add_fan_lm75a_temp_sensor(void);
int config_add_fan_analog_temp_sensor(void);
int config_add_fan_soft_temp_sensor(void);
int config_del_fan_lm75a_temp_sensor(void);
int config_del_fan_analog_temp_sensor(void);
int config_del_fan_soft_temp_sensor(void);
int config_add_fan_curve_point(void);
int config_del_fan_curve_point(void);
int config_get_fan_n_curve_points(void);
int config_get_fan_curve_point(void);

int config_get_fan_max_rpm(void);
int config_set_fan_max_rpm(void);
int config_get_fan_min_rpm(void);
int config_set_fan_min_rpm(void);
int config_get_fan_rpm(void);

int config_get_fan_hysterisis(void);
int config_set_fan_hysterisis(void);

int config_get_fan_mode(void);
int config_switch_fan_mode(void);
int config_get_fan_adc_value(void);
int config_get_fan_output(void);
int config_set_fan_output(void);
int config_set_fan_output_auto(void);
int config_get_fan_duty_cycle_response(void);
int config_set_fan_duty_cycle_response(void);
int config_set_fan_proportional_duty_cycle_response(void);
int config_get_fan_voltage_response(void);
int config_set_fan_voltage_response(void);
int config_set_fan_proportional_voltage_response(void);
int config_get_fan_mode_transitions(void);
int config_set_fan_mode_transitions(void);

int config_calibrate_fan_voltage_response(void);
int config_calibrate_fan_duty_cycle_response(void);

int config_exit(void);

#endif
