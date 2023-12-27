#include "controller_default_device_cmd.h"

void device_overtemp_cmd(struct cmd const* const)
{
  fprintf(stderr,"%s: Error: Device is overheating!\n",__func__);
}

void lm75a_temp_sensor_alarm_cmd(struct cmd const* const cmd)
{
  fprintf(stderr,"%s: Warning: LM75a temperature device(s) are above temperature alarm threshold: ",__func__);
  int i;

  for(i=7; i>=0; --i) fprintf(stderr, "%u",(cmd->bytes[0]>>i)&1);
  fprintf(stderr,"\n");
}

void analog_temp_sensor_alarm_cmd(struct cmd const* const cmd)
{
  fprintf(stderr,"%s: Warning: Analog temperature device(s) are above temperature alarm threshold: ",__func__);
  int i;

  for(i=7; i>=0; --i) fprintf(stderr, "%u",(cmd->bytes[0]>>i)&1);
  fprintf(stderr,"\n");
}

void soft_temp_sensor_alarm_cmd(struct cmd const* const cmd)
{
  fprintf(stderr,"%s: Warning: Soft temperature device(s) are above temperature alarm threshold: ",__func__);
  int i;

  for(i=7; i>=0; --i) fprintf(stderr, "%u",(cmd->bytes[0]>>i)&1);
  fprintf(stderr,"\n");
}
