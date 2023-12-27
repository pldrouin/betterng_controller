#include "controller.h"

struct globals gGlobals;

int main(int nargs, const char* args[])
{

  if(nargs<2) {
    fprintf(stderr,"Usage: %s device baud_rate [commands]\n",args[0]);
    return 1;
  }

  sl_set_callback(DEVICE_OVERTEMP_CMD_ID, device_overtemp_cmd);

  sl_set_callback(LM75A_TEMP_SENSOR_ALARM_CMD_ID, lm75a_temp_sensor_alarm_cmd);
  sl_set_callback(ANALOG_TEMP_SENSOR_ALARM_CMD_ID, lm75a_temp_sensor_alarm_cmd);
  sl_set_callback(SOFT_TEMP_SENSOR_ALARM_CMD_ID, lm75a_temp_sensor_alarm_cmd);

  fprintf(stderr,"Opening '%s'\n",args[1]);

  sl_init(&gGlobals.sl_dev);

  if(sl_start(&gGlobals.sl_dev, args[1], UART_BAUDRATE)<0) return -1;

  args+=2;
  nargs-=2;
  gGlobals.nargs=nargs;
  gGlobals.args=args;

  config(args, nargs);

  sl_close(&gGlobals.sl_dev);

  return 0;
}
