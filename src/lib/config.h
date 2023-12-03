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
  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {\
    fprintf(stderr,"%s: Error: Missing fan ID!\n",__func__);\
    return -1;\
  }\
  sscanf(gGlobals.pbuf, "%" SCNu8, &id);\
})

int config_get_fan_rpm(void);
int config_get_fan_off_level(void);
int config_get_fan_voltage(void);
int config_get_fan_voltage_target(void);
int config_fan_adc_calibration(void);
int config_switch_fan_control(void);
int config_get_fan_output(void);
int config_set_fan_output(void);
int config_set_fan_output_auto(void);
int config_get_fan_duty_cycle_response(void);
int config_set_fan_duty_cycle_response(void);
int config_get_fan_voltage_response(void);
int config_set_fan_voltage_response(void);
int config_get_fan_mode_transitions(void);
int config_set_fan_mode_transitions(void);

int config_calibrate_fan_voltage_response(void);
int config_calibrate_fan_duty_cycle_response(void);

#endif
