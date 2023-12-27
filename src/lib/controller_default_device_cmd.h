#ifndef _CONTROLLER_DEFAULT_DEVICE_CMD_
#define _CONTROLLER_DEFAULT_DEVICE_CMD_

#include <stdio.h>

#include "serial_link.h"

void device_overtemp_cmd(struct cmd const* const);

void lm75a_temp_sensor_alarm_cmd(struct cmd const* const cmd);
void analog_temp_sensor_alarm_cmd(struct cmd const* const cmd);
void soft_temp_sensor_alarm_cmd(struct cmd const* const cmd);

#endif
