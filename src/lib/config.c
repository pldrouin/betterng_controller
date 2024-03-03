#include "config.h"

#define HT_SET_FUNC(func) (ht_set(gGlobals.ht, #func, config_ ## func))

int config(int nargs, const char** args)
{
  args_init(&gGlobals.a_h, nargs, args);

  gGlobals.plength=1;

  gGlobals.oout=1; //stdout==1
  gGlobals.eout=2; //stderr==2
  
  gGlobals.interactive=false;
 
  gGlobals.ht=ht_create();
  config_ht_populate();

  gGlobals.oldstdout=dup(1);
  gGlobals.oldstderr=dup(2);

  int (*cfunct)(void);

  while(gGlobals.plength>0) {

    while((gGlobals.plength=getnextparam(&gGlobals.a_h,false,gGlobals.pbuf,PBUF_SIZE))>0) {
      cfunct=(int (*)(void))ht_get(gGlobals.ht, gGlobals.pbuf);

      if(cfunct) {

	if(cfunct()) {
	  fprintf(stderr,"%s: Error: Invalid command!\n",__func__);
	  ht_destroy(gGlobals.ht);
	  return 1;
	}

      } else {
	fprintf(stderr,"%s: Error: Unknown parameter: '%s'\n",__func__,gGlobals.pbuf);
	ht_destroy(gGlobals.ht);
	return 1;
      }
    }

    //Assertion: We are ready to perform a task whether a break statement has
    //been reached in the inner loop or plength<=0. Otherwise the value of
    //plength can be assessed and appropriate actions can be taken

    //All the parameters for the current job have been read, the job can now be
    //performed. Do it here

    //If reading argument from the standard input (interactive mode), we
    //indicate that the job is completed through the standard output
    if(gGlobals.interactive) {
      write(gGlobals.oldstderr,"@DONE\n",6);
      gGlobals.interactive=false;
    }
    fflush(stdout);
    fflush(stderr);
    //Continue reading other commands for the next job
  }

  close(gGlobals.oout);
  close(gGlobals.eout);
  dup2(gGlobals.oldstdout,1);
  dup2(gGlobals.oldstderr,2);
  close(gGlobals.oldstdout);
  close(gGlobals.oldstderr);

  args_terminate(&gGlobals.a_h);
  ht_destroy(gGlobals.ht);
  return 0;
}

void config_ht_populate()
{
  HT_SET_FUNC(config);

  HT_SET_FUNC(help);
  HT_SET_FUNC(olog);
  HT_SET_FUNC(elog);
  HT_SET_FUNC(prompt);

  HT_SET_FUNC(ping);
  HT_SET_FUNC(reset);

  HT_SET_FUNC(eeprom_save);

  HT_SET_FUNC(get_lm75a_temp_sensor_list);
  HT_SET_FUNC(add_lm75a_temp_sensor);
  HT_SET_FUNC(del_lm75a_temp_sensor);
  HT_SET_FUNC(get_analog_temp_sensor_list);
  HT_SET_FUNC(add_analog_temp_sensor);
  HT_SET_FUNC(del_analog_temp_sensor);
  HT_SET_FUNC(get_analog_temp_sensor_adc_value);
  HT_SET_FUNC(get_lm75a_temp_sensor_value);
  HT_SET_FUNC(get_analog_temp_sensor_value);
  HT_SET_FUNC(get_soft_temp_sensor_value);
  HT_SET_FUNC(get_lm75a_temp_sensor_calib);
  HT_SET_FUNC(get_analog_temp_sensor_calib0);
  HT_SET_FUNC(get_analog_temp_sensor_calib1);
  HT_SET_FUNC(set_lm75a_temp_sensor_calib);
  HT_SET_FUNC(set_analog_temp_sensor_calib0);
  HT_SET_FUNC(set_analog_temp_sensor_calib1);
  HT_SET_FUNC(set_soft_temp_sensor_value);

  HT_SET_FUNC(get_lm75a_temp_sensor_alarm_value);
  HT_SET_FUNC(get_analog_temp_sensor_alarm_value);
  HT_SET_FUNC(get_soft_temp_sensor_alarm_value);
  HT_SET_FUNC(set_lm75a_temp_sensor_alarm_value);
  HT_SET_FUNC(set_analog_temp_sensor_alarm_value);
  HT_SET_FUNC(set_soft_temp_sensor_alarm_value);

  HT_SET_FUNC(get_fan_list);
  HT_SET_FUNC(add_fan);
  HT_SET_FUNC(del_fan);
  HT_SET_FUNC(get_fan_lm75a_temp_sensor_list);
  HT_SET_FUNC(get_fan_analog_temp_sensor_list);
  HT_SET_FUNC(get_fan_soft_temp_sensor_list);
  HT_SET_FUNC(add_fan_lm75a_temp_sensor);
  HT_SET_FUNC(add_fan_analog_temp_sensor);
  HT_SET_FUNC(add_fan_soft_temp_sensor);
  HT_SET_FUNC(del_fan_lm75a_temp_sensor);
  HT_SET_FUNC(del_fan_analog_temp_sensor);
  HT_SET_FUNC(del_fan_soft_temp_sensor);
  HT_SET_FUNC(add_fan_curve_point);
  HT_SET_FUNC(del_fan_curve_point);
  HT_SET_FUNC(get_fan_n_curve_points);
  HT_SET_FUNC(get_fan_curve_point);

  HT_SET_FUNC(get_fan_hysterisis);
  HT_SET_FUNC(set_fan_hysterisis);

  HT_SET_FUNC(get_fan_max_rpm);
  HT_SET_FUNC(set_fan_max_rpm);
  HT_SET_FUNC(get_fan_min_rpm);
  HT_SET_FUNC(set_fan_min_rpm);
  HT_SET_FUNC(get_fan_rpm);

  HT_SET_FUNC(get_fan_mode);
  HT_SET_FUNC(switch_fan_mode);
  HT_SET_FUNC(get_fan_adc_value);
  HT_SET_FUNC(get_fan_output);
  HT_SET_FUNC(set_fan_output);
  HT_SET_FUNC(set_fan_output_auto);
  HT_SET_FUNC(get_fan_duty_cycle_response);
  HT_SET_FUNC(set_fan_duty_cycle_response);
  HT_SET_FUNC(set_fan_proportional_duty_cycle_response);
  HT_SET_FUNC(get_fan_voltage_response);
  HT_SET_FUNC(set_fan_voltage_response);
  HT_SET_FUNC(set_fan_proportional_voltage_response);
  HT_SET_FUNC(calibrate_fan_voltage_response);
  HT_SET_FUNC(calibrate_fan_duty_cycle_response);
  HT_SET_FUNC(get_fan_mode_transitions);
  HT_SET_FUNC(set_fan_mode_transitions);

  HT_SET_FUNC(exit);
}

int config_help(void)
{
  printf(BSTR "config" UBSTR " configuration_file\n"); 
  printf(BSTR "olog" UBSTR " output_log_file\n"); 
  printf(BSTR "elog" UBSTR " error_log_file\n"); 
  printf(BSTR "prompt" UBSTR "\n"); 
  printf(BSTR "eeprom_save" UBSTR "\n");
  printf(BSTR "get_lm75a_temp_sensor_list" UBSTR "\n");
  printf(BSTR "add_lm75a_temp_sensor" UBSTR " id\n");
  printf(BSTR "del_lm75a_temp_sensor" UBSTR " id\n");
  printf(BSTR "get_analog_temp_sensor_list" UBSTR "\n");
  printf(BSTR "add_analog_temp_sensor" UBSTR " id\n");
  printf(BSTR "del_analog_temp_sensor" UBSTR " id\n");
  printf(BSTR "get_analog_temp_sensor_adc_value" UBSTR " id\n");
  printf(BSTR "get_lm75a_temp_sensor_value" UBSTR " id\n");
  printf(BSTR "get_analog_temp_sensor_value" UBSTR " id\n");
  printf(BSTR "get_soft_temp_sensor_value" UBSTR " id\n");
  printf(BSTR "get_lm75a_temp_sensor_calib" UBSTR " id\n");
  printf(BSTR "get_analog_temp_sensor_calib0" UBSTR " id\n");
  printf(BSTR "get_analog_temp_sensor_calib1" UBSTR " id\n");
  printf(BSTR "set_lm75a_temp_sensor_calib" UBSTR " id a0 a1 a2\n");
  printf(BSTR "set_analog_temp_sensor_calib0" UBSTR " id a0 a1\n");
  printf(BSTR "set_analog_temp_sensor_calib1" UBSTR " id a2 shift\n");
  printf(BSTR "set_soft_temp_sensor_value" UBSTR " id value\n");
  printf(BSTR "get_lm75a_temp_sensor_alarm_value" UBSTR " id\n");
  printf(BSTR "get_analog_temp_sensor_alarm_value" UBSTR " id\n");
  printf(BSTR "get_soft_temp_sensor_alarm_value" UBSTR " id\n");
  printf(BSTR "set_lm75a_temp_sensor_alarm_value" UBSTR " id alarm_value\n");
  printf(BSTR "set_analog_temp_sensor_alarm_value" UBSTR " id alarm_value\n");
  printf(BSTR "set_soft_temp_sensor_alarm_value" UBSTR " id alarm_value\n");
  printf(BSTR "get_fan_list" UBSTR "\n");
  printf(BSTR "add_fan" UBSTR " id\n");
  printf(BSTR "del_fan" UBSTR " id\n");
  printf(BSTR "get_fan_lm75a_temp_sensor_list" UBSTR " fan_id\n");
  printf(BSTR "get_fan_analog_temp_sensor_list" UBSTR " fan_id\n");
  printf(BSTR "get_fan_soft_temp_sensor_list" UBSTR " fan_id\n");
  printf(BSTR "add_fan_lm75a_temp_sensor" UBSTR " fan_id sens_id\n");
  printf(BSTR "add_fan_analog_temp_sensor" UBSTR " fan_id sens_id\n");
  printf(BSTR "add_fan_soft_temp_sensor" UBSTR " fan_id sens_id\n");
  printf(BSTR "del_fan_lm75a_temp_sensor" UBSTR " fan_id sens_id\n");
  printf(BSTR "del_fan_analog_temp_sensor" UBSTR " fan_id sens_id\n");
  printf(BSTR "del_fan_soft_temp_sensor" UBSTR " fan_id sens_id\n");
  printf(BSTR "add_fan_curve_point" UBSTR " fan_id temp output\n");
  printf(BSTR "del_fan_curve_point" UBSTR " fan_id index\n");
  printf(BSTR "get_fan_n_curve_points" UBSTR " fan_id\n");
  printf(BSTR "get_fan_curve_point" UBSTR " fan_id index\n");
  printf(BSTR "get_fan_hysterisis" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_hysterisis" UBSTR " fan_id hysterisis\n"); 
  printf(BSTR "get_fan_max_rpm" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_max_rpm" UBSTR " fan_id max_rpm\n"); 
  printf(BSTR "get_fan_min_rpm" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_min_rpm" UBSTR " fan_id min_rpm\n"); 
  printf(BSTR "get_fan_rpm" UBSTR " fan_id\n"); 
  printf(BSTR "get_fan_mode" UBSTR " fan_id\n"); 
  printf(BSTR "switch_fan_mode" UBSTR " fan_id voltage/pwm/voltage_auto/pwm_auto\n"); 
  printf(BSTR "get_fan_adc_value" UBSTR " fan_id\n"); 
  printf(BSTR "get_fan_output" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_output" UBSTR " fan_id 0-255\n"); 
  printf(BSTR "set_fan_output_auto" UBSTR " fan_id 0-255\n"); 
  printf(BSTR "get_fan_duty_cycle_response" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_duty_cycle_response" UBSTR " fan_id dc_no_out ddcdout\n"); 
  printf(BSTR "set_fan_proportional_duty_cycle_response" UBSTR " fan_id\n"); 
  printf(BSTR "get_fan_voltage_response" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_voltage_response" UBSTR " fan_id v_no_out dvdout\n"); 
  printf(BSTR "set_fan_proportional_voltage_response" UBSTR " fan_id\n"); 
  printf(BSTR "calibrate_fan_duty_cycle_response" UBSTR " fan_id low_duty_cycle mid_duty_cycle|0\n"); 
  printf(BSTR "calibrate_fan_voltage_response" UBSTR " fan_id low_proportional_output mid_proportional_output|0\n"); 
  printf(BSTR "get_fan_mode_transitions" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_mode_transitions" UBSTR " fan_id pwm_to_voltage_output voltage_to_pwm_output\n"); 

  printf(BSTR "exit" UBSTR "\n"); 
  return 0;
}

int config_config(void)
{
  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing configuration file name!\n",__func__);
    return -1;
  }

  if(args_open_conf_file(&gGlobals.a_h, gGlobals.pbuf)) {
    fprintf(stderr,"%s: Error: Error while trying to open configuration file!\n",__func__);
    return -1;
  }

  //If we switch to interactive mode (reading instructions from standard
  //input)
  if(args_reading_from_stdin(&gGlobals.a_h)) {

    gGlobals.interactive=true;
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    write(gGlobals.oldstderr,"@INTERACTIVE\n",13);
    #pragma GCC diagnostic push

    //Otherwise, if reading from a configuration file
  } else {
    printf("Reading from config file %s\n",gGlobals.pbuf);
  }
  return 0;
}

//Output file log, redirecting the standard output
int config_olog(void)
{
  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing output log file name!\n",__func__);
    return -1;
  }
  fflush(stdout);
  close(gGlobals.oout);

  if((gGlobals.oout=open(gGlobals.pbuf,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))<0) {
    fprintf(stderr,"%s: Error: Cannot open file '%s' in write mode\n",__func__,gGlobals.pbuf);
    ht_destroy(gGlobals.ht);
    return 1;
  }
  dup2(gGlobals.oout,1);
  return 0;
}

//Output error file log, redirecting the standard error
int config_elog(void)
{
  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing error log file name!\n",__func__);
    return -1;
  }
  fflush(stderr);
  close(gGlobals.eout);

  if((gGlobals.eout=open(gGlobals.pbuf,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))<0) {
    fprintf(stderr,"%s: Error: cannot open file '%s' in write mode\n",__func__,gGlobals.pbuf);
    ht_destroy(gGlobals.ht);
    return 1;
  }
  dup2(gGlobals.eout,2);
  return 0;
}

int prompt_callback(const char* param, void* ptr) {
  struct globals* globals=(struct globals*)ptr;

  int (*cfunct)(void)=(int (*)(void))ht_get(gGlobals.ht, param);
  int cret;

  if(cfunct) {
    cret=cfunct();

    if(cret == CONFIG_EXIT_RET) return ARGS_CB_EXIT;

  } else {
    fprintf(stderr,"%s: Error: Unknown command: '%s'\n",__func__,param);
    return -1;
  }
  return ARGS_CB_OK;
}

int config_prompt(void)
{
    return args_prompt(&gGlobals.a_h, "<bigng> ", gGlobals.pbuf, PBUF_SIZE, prompt_callback, &gGlobals);
}

int config_ping(void)
{
  int ret=send_receive_ping_cmd();

  if(ret) fprintf(stderr,"%s: Error: Ping failed with error %i!\n",__func__, ret);
  return ret;
}

int config_reset(void)
{
  int ret=send_receive_reset_cmd();

  if(ret) fprintf(stderr,"%s: Error: Reset failed with error %i!\n",__func__, ret);
  return ret;
}

int config_eeprom_save(void)
{
  int ret=send_receive_eeprom_save_cmd();

  if(ret) {
    fprintf(stderr,"%s: Error: EEPROM save failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_lm75a_temp_sensor_list(void)
{
  uint8_t list;
  int ret=send_receive_get_lm75a_temp_sensor_list_cmd(&list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get LM75a temperature sensor list failed with error %i!\n",__func__, ret);
    return ret;
  }
  int i;
  for(i=7; i>=0; --i) printf("%i",(list>>i)&1);
  printf("\n");
  return 0;
}

int config_add_lm75a_temp_sensor(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int ret=send_receive_add_lm75a_temp_sensor_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add LM75a temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_lm75a_temp_sensor(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int ret=send_receive_del_lm75a_temp_sensor_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add LM75a temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_analog_temp_sensor_list(void)
{
  uint8_t list;
  int ret=send_receive_get_analog_temp_sensor_list_cmd(&list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get analog temperature sensor list failed with error %i!\n",__func__, ret);
    return ret;
  }
  int i;
  for(i=7; i>=0; --i) printf("%i",(list>>i)&1);
  printf("\n");
  return 0;
}

int config_add_analog_temp_sensor(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int ret=send_receive_add_analog_temp_sensor_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add analog temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_analog_temp_sensor(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int ret=send_receive_del_analog_temp_sensor_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Delete analog temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_analog_temp_sensor_adc_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  uint16_t adc_value;
  int ret=send_receive_get_analog_temp_sensor_adc_value_cmd(id, &adc_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get analog temperature sensor ADC value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("0x%04X\t%" SCNu16 "\n", adc_value, adc_value);
  return 0;
}

int config_get_lm75a_temp_sensor_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t value;
  int ret=send_receive_get_lm75a_temp_sensor_value_cmd(id, &value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get LM75a temperature sensor value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i/256 (%.2f) C\n", value, value/256.);
  return 0;
}

int config_get_analog_temp_sensor_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t value;
  int ret=send_receive_get_analog_temp_sensor_value_cmd(id, &value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get analog temperature sensor value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i/256 (%.2f) C\n", value, value/256.);
  return 0;
}

int config_get_soft_temp_sensor_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t value;
  int ret=send_receive_get_soft_temp_sensor_value_cmd(id, &value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get soft temperature sensor value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i/256 (%.2f) C\n", value, value/256.);
  return 0;
}

int config_get_lm75a_temp_sensor_calib(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t a0, a1, a2;
  int ret=send_receive_get_lm75a_temp_sensor_calib_cmd(id, &a0, &a1, &a2);

  if(ret) {
    fprintf(stderr,"%s: Error: Get LM75a temperature sensor calibration failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("a0 = %" SCNi16 " / 256 C\n", a0);
  printf("a1 = %" SCNi16 " / (256 * 2^14) C\n", a1);
  printf("a2 = %" SCNi16 " / (256 * 2^28) C\n", a2);
  return 0;
}

int config_get_analog_temp_sensor_calib0(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  float a0, a1;
  int ret=send_receive_get_analog_temp_sensor_calib0_cmd(id, &a0, &a1);

  if(ret) {
    fprintf(stderr,"%s: Error: Get analog temperature sensor calibration 0 failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("a0 = %22.15f\n", a0);
  printf("a1 = %22.15f\n", a1);
  return 0;
}

int config_get_analog_temp_sensor_calib1(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  float a2;
  int16_t shift;
  int ret=send_receive_get_analog_temp_sensor_calib1_cmd(id, &a2, &shift);

  if(ret) {
    fprintf(stderr,"%s: Error: Get analog temperature sensor calibration 1 failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("a2 = %22.15f\n", a2);
  printf("shift = %" SCNi16 " / 256 C\n", shift);
  return 0;
}

int config_set_lm75a_temp_sensor_calib(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t a0, a1, a2;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing a0 parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &a0);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing a1 parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &a1);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing a2 parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &a2);
  int ret=send_receive_set_lm75a_temp_sensor_calib_cmd(id, a0, a1, a2);

  if(ret) {
    fprintf(stderr,"%s: Error: Set LM75a temperature sensor calibration failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_analog_temp_sensor_calib0(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  float a0, a1;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing a0 parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%f", &a0);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing a1 parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%f", &a1);

  int ret=send_receive_set_analog_temp_sensor_calib0_cmd(id, a0, a1);

  if(ret) {
    fprintf(stderr,"%s: Error: Set analog temperature sensor calibration 0 failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_analog_temp_sensor_calib1(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  float a2;
  int16_t shift;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing a2 parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%f", &a2);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing shift parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &shift);

  int ret=send_receive_set_analog_temp_sensor_calib1_cmd(id, a2, shift);

  if(ret) {
    fprintf(stderr,"%s: Error: Set analog temperature sensor calibration 1 failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_soft_temp_sensor_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t value;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing value parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &value);

  int ret=send_receive_set_soft_temp_sensor_value_cmd(id, value);

  if(ret) {
    fprintf(stderr,"%s: Error: Set soft temperature sensor value failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_lm75a_temp_sensor_alarm_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t alarm_value;
  int ret=send_receive_get_lm75a_temp_sensor_alarm_value_cmd(id, &alarm_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get LM75A temperature sensor alarm_value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i/256 (%.2f) C\n", alarm_value, alarm_value/256.);
  return 0;
}

int config_get_analog_temp_sensor_alarm_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t alarm_value;
  int ret=send_receive_get_analog_temp_sensor_alarm_value_cmd(id, &alarm_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get analog temperature sensor alarm_value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i/256 (%.2f) C\n", alarm_value, alarm_value/256.);
  return 0;
}

int config_get_soft_temp_sensor_alarm_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t alarm_value;
  int ret=send_receive_get_soft_temp_sensor_alarm_value_cmd(id, &alarm_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get soft temperature sensor alarm_value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i/256 (%.2f) C\n", alarm_value, alarm_value/256.);
  return 0;
}

int config_set_lm75a_temp_sensor_alarm_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t alarm_value;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing alarm_value parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &alarm_value);

  int ret=send_receive_set_lm75a_temp_sensor_alarm_value_cmd(id, alarm_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Set LM75A temperature sensor alarm value failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_analog_temp_sensor_alarm_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t alarm_value;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing alarm_value parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &alarm_value);

  int ret=send_receive_set_analog_temp_sensor_alarm_value_cmd(id, alarm_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Set analog temperature sensor alarm value failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_soft_temp_sensor_alarm_value(void)
{
  uint8_t id;
  CONFIG_GET_SENSOR_ID(id);
  int16_t alarm_value;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing alarm_value parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi16, &alarm_value);

  int ret=send_receive_set_soft_temp_sensor_alarm_value_cmd(id, alarm_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Set soft temperature sensor alarm value failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_list(void)
{
  uint8_t list;
  int ret=send_receive_get_fan_list_cmd(&list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan list failed with error %i!\n",__func__, ret);
    return ret;
  }
  int i;
  for(i=7; i>=0; --i) printf("%i",(list>>i)&1);
  printf("\n");
  return 0;
}

int config_add_fan(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int ret=send_receive_add_fan_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add fan failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_fan(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int ret=send_receive_del_fan_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Delete fan failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_lm75a_temp_sensor_list(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  uint8_t list;
  int ret=send_receive_get_fan_lm75a_temp_sensor_list_cmd(fan_id, &list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan LM75a temperature sensor list failed with error %i!\n",__func__, ret);
    return ret;
  }
  int i;
  for(i=7; i>=0; --i) printf("%i",(list>>i)&1);
  printf("\n");
  return 0;
}

int config_get_fan_analog_temp_sensor_list(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  uint8_t list;
  int ret=send_receive_get_fan_analog_temp_sensor_list_cmd(fan_id, &list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan analog temperature sensor list failed with error %i!\n",__func__, ret);
    return ret;
  }
  int i;
  for(i=7; i>=0; --i) printf("%i",(list>>i)&1);
  printf("\n");
  return 0;
}

int config_get_fan_soft_temp_sensor_list(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  uint8_t list;
  int ret=send_receive_get_fan_soft_temp_sensor_list_cmd(fan_id, &list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan soft temperature sensor list failed with error %i!\n",__func__, ret);
    return ret;
  }
  int i;
  for(i=7; i>=0; --i) printf("%i",(list>>i)&1);
  printf("\n");
  return 0;
}

int config_add_fan_lm75a_temp_sensor(void)
{
  uint8_t fan_id, sens_id;
  CONFIG_GET_FAN_ID(fan_id);
  CONFIG_GET_SENSOR_ID(sens_id);
  int ret=send_receive_add_fan_lm75a_temp_sensor_cmd(fan_id, sens_id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add fan LM75a temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_add_fan_analog_temp_sensor(void)
{
  uint8_t fan_id, sens_id;
  CONFIG_GET_FAN_ID(fan_id);
  CONFIG_GET_SENSOR_ID(sens_id);
  int ret=send_receive_add_fan_analog_temp_sensor_cmd(fan_id, sens_id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add fan analog temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_add_fan_soft_temp_sensor(void)
{
  uint8_t fan_id, sens_id;
  CONFIG_GET_FAN_ID(fan_id);
  CONFIG_GET_SENSOR_ID(sens_id);
  int ret=send_receive_add_fan_soft_temp_sensor_cmd(fan_id, sens_id);

  if(ret) {
    fprintf(stderr,"%s: Error: Add fan soft temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_fan_lm75a_temp_sensor(void)
{
  uint8_t fan_id, sens_id;
  CONFIG_GET_FAN_ID(fan_id);
  CONFIG_GET_SENSOR_ID(sens_id);
  int ret=send_receive_del_fan_lm75a_temp_sensor_cmd(fan_id, sens_id);

  if(ret) {
    fprintf(stderr,"%s: Error: Delete fan LM75a temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_fan_analog_temp_sensor(void)
{
  uint8_t fan_id, sens_id;
  CONFIG_GET_FAN_ID(fan_id);
  CONFIG_GET_SENSOR_ID(sens_id);
  int ret=send_receive_del_fan_analog_temp_sensor_cmd(fan_id, sens_id);

  if(ret) {
    fprintf(stderr,"%s: Error: Delete fan analog temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_fan_soft_temp_sensor(void)
{
  uint8_t fan_id, sens_id;
  CONFIG_GET_FAN_ID(fan_id);
  CONFIG_GET_SENSOR_ID(sens_id);
  int ret=send_receive_del_fan_soft_temp_sensor_cmd(fan_id, sens_id);

  if(ret) {
    fprintf(stderr,"%s: Error: Delete fan soft temperature sensor failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_add_fan_curve_point(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  int8_t temp;
  
  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing temperature parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNi8, &temp);
  uint8_t output;
  
  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing output parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNu8, &output);
  int ret=send_receive_add_fan_curve_point_cmd(fan_id, temp, output);

  if(ret) {
    fprintf(stderr,"%s: Error: Add fan curve point failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_del_fan_curve_point(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  uint8_t index;
  
  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan curve point index parameter!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf,"%" SCNu8, &index);
  int ret=send_receive_del_fan_curve_point_cmd(fan_id, index);

  if(ret) {
    fprintf(stderr,"%s: Error: Delete fan curve point failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_n_curve_points(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  uint8_t ncurvepoints;
  int ret=send_receive_get_fan_n_curve_points_cmd(fan_id, &ncurvepoints);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan number of curve points failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%" SCNu8 "\n",ncurvepoints);
  return 0;
}

int config_get_fan_curve_point(void)
{
  uint8_t fan_id;
  CONFIG_GET_FAN_ID(fan_id);
  uint8_t index;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan curve point index value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &index);
  int8_t temp;
  uint8_t output;
  int ret=send_receive_get_fan_curve_point_cmd(fan_id, index, &temp, &output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan curve point failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%" SCNi8": %" SCNu8 "\n",temp,output);
  return 0;
}

int config_get_fan_hysterisis(void)
{
  uint8_t id;
  uint8_t hysterisis;
  CONFIG_GET_FAN_ID(id);

  int ret=send_receive_get_fan_hysterisis_cmd(id, &hysterisis);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan hysterisis failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%u C\n",hysterisis);
  return 0;
}

int config_set_fan_hysterisis(void)
{
  uint8_t id;
  uint8_t hysterisis;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan hysterisis value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &hysterisis);

  int ret=send_receive_set_fan_hysterisis_cmd(id, hysterisis);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan hysterisis failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_max_rpm(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int16_t max_rpm;
  int ret=send_receive_get_fan_max_rpm_cmd(id, &max_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan max RPM failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i\n", max_rpm);
  return 0;
}

int config_set_fan_max_rpm(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int16_t max_rpm;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan max RPM value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNi16, &max_rpm);

  if(max_rpm<=0) {
    fprintf(stderr,"%s: Error: Fan max RPM value must be strictly positive!\n",__func__);
    return -1;
  }
  int ret=send_receive_set_fan_max_rpm_cmd(id, max_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Set max fan RPM failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_min_rpm(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int16_t min_rpm;
  int ret=send_receive_get_fan_min_rpm_cmd(id, &min_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan min RPM failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i\n", min_rpm);
  return 0;
}

int config_set_fan_min_rpm(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int16_t min_rpm;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan min RPM value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNi16, &min_rpm);

  if(min_rpm<=0) {
    fprintf(stderr,"%s: Error: Fan min RPM value must be strictly positive!\n",__func__);
    return -1;
  }
  int ret=send_receive_set_fan_min_rpm_cmd(id, min_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Set min fan RPM failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_rpm(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int16_t rpm;
  int ret=send_receive_get_fan_rpm_cmd(id, &rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan RPM failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%i\n", rpm);
  return 0;
}

int config_get_fan_mode(void)
{
  uint8_t id;
  uint8_t mode;
  CONFIG_GET_FAN_ID(id);

  int ret=send_receive_get_fan_mode_cmd(id, &mode);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan mode failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%u\n",mode);
  return 0;
}

int config_switch_fan_mode(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan mode!\n",__func__);
    return -1;
  }
  tolowerstr(gGlobals.pbuf);
  uint8_t mode;

  if(!argsdiffer(gGlobals.pbuf, "voltage")) mode=FAN_VOLTAGE_MODE;

  else if(!argsdiffer(gGlobals.pbuf, "pwm")) mode=FAN_PWM_MODE;

  else if(!argsdiffer(gGlobals.pbuf, "voltage_auto")) mode=FAN_VOLTAGE_MODE|FAN_AUTO_FLAG;

  else if(!argsdiffer(gGlobals.pbuf, "pwm_auto")) mode=FAN_PWM_MODE|FAN_AUTO_FLAG;

  else {
    fprintf(stderr, "%s: Error: Fan control mode '%s' is invalid!\n", __func__, gGlobals.pbuf);
    return -1;
  }
  int ret=send_receive_switch_fan_mode_cmd(id, mode);

  if(ret) {
    fprintf(stderr,"%s: Error: Switch fan control mode failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_adc_value(void)
{
  uint8_t id;
  uint16_t adc_value;
  CONFIG_GET_FAN_ID(id);

  int ret=send_receive_get_fan_adc_value_cmd(id, &adc_value);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan adc value failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("0x%04X\t%" SCNu16 "\n", adc_value, adc_value);
  return 0;
}

int config_get_fan_output(void)
{
  uint8_t id;
  uint8_t output;
  CONFIG_GET_FAN_ID(id);

  int ret=send_receive_get_fan_output_cmd(id, &output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan output failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("%u\n",output);
  return 0;
}

int config_set_fan_output(void)
{
  uint8_t id;
  uint8_t output;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &output);
  int ret=send_receive_set_fan_output_cmd(id, output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan output failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_fan_output_auto(void)
{
  uint8_t id;
  uint8_t output;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &output);
  int ret=send_receive_set_fan_output_auto_cmd(id, output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan output failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_duty_cycle_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t dcnoout;
  int16_t ddcdout;
  int16_t d2dcdout2;

  int ret=send_receive_get_fan_duty_cycle_response_cmd(id, &dcnoout, &ddcdout, &d2dcdout2);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan duty cycle response failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("dc_no_out: %u /64\n",dcnoout);
  printf("ddcdout: %i /64 at max output\n",ddcdout);
  printf("d2dcdout2: %i /64 mV at max output^2\n",d2dcdout2);
  return 0;
}

int config_set_fan_duty_cycle_response(void)
{
  uint8_t id;
  uint16_t dcnoout;
  int16_t ddcdout;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan dc_no_out value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu16, &dcnoout);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan ddcdout value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNi16, &ddcdout);
  int ret=send_receive_set_fan_duty_cycle_response_cmd(id, dcnoout, ddcdout);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan duty cycle response failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_fan_proportional_duty_cycle_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int ret=send_receive_set_fan_proportional_duty_cycle_response_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan proportional duty cycle response failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_voltage_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t vnoout;
  int16_t dvdout;
  int16_t d2vdout2;

  int ret=send_receive_get_fan_voltage_response_cmd(id, &vnoout, &dvdout, &d2vdout2);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan voltage response failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("v_no_out: %u mV\n",vnoout);
  printf("dvdout: %i mV at max output\n",dvdout);
  printf("d2vdout2: %u mV at max output^2\n",d2vdout2);
  return 0;
}

int config_set_fan_voltage_response(void)
{
  uint8_t id;
  uint16_t vnoout;
  int16_t dvdout;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan v_no_out value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu16, &vnoout);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan dvdout value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNi16, &dvdout);
  int ret=send_receive_set_fan_voltage_response_cmd(id, vnoout, dvdout);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan voltage response failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_set_fan_proportional_voltage_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int ret=send_receive_set_fan_proportional_voltage_response_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan proportional voltage response failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_calibrate_fan_voltage_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t low_proportional_output, mid_proportional_output;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan low_proportional_output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu16, &low_proportional_output);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan mid_proportional_output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu16, &mid_proportional_output);
  int ret=calibrate_fan_voltage_response_cmd(id, low_proportional_output, mid_proportional_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Calibrate fan voltage response failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_calibrate_fan_duty_cycle_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint8_t min_duty_cycle, mid_duty_cycle;

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan min_duty_cycle value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &min_duty_cycle);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan mid_duty_cycle value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &mid_duty_cycle);
  int ret=calibrate_fan_duty_cycle_response_cmd(id, min_duty_cycle, mid_duty_cycle);

  if(ret) {
    fprintf(stderr,"%s: Error: Calibrate fan duty cycle response failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_get_fan_mode_transitions(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint8_t pwm_to_voltage_output;
  uint8_t voltage_to_pwm_output;

  int ret=send_receive_get_fan_mode_transitions_cmd(id, &pwm_to_voltage_output, &voltage_to_pwm_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan mode transitions failed with error %i!\n",__func__, ret);
    return ret;
  }
  printf("pwm_to_voltage_output: %u\n",pwm_to_voltage_output);
  printf("voltage_to_pwm_output: %u\n",voltage_to_pwm_output);
  return 0;
}

int config_set_fan_mode_transitions(void)
{
  uint8_t id;
  uint8_t pwm_to_voltage_output;
  uint8_t voltage_to_pwm_output;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan pwm_to_voltage_output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &pwm_to_voltage_output);

  if(getnextparam(&gGlobals.a_h,true,gGlobals.pbuf,PBUF_SIZE)<0) {
    fprintf(stderr,"%s: Error: Missing fan voltage_to_pwm_output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNi8, &voltage_to_pwm_output);
  int ret=send_receive_set_fan_mode_transitions_cmd(id, pwm_to_voltage_output, voltage_to_pwm_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan mode transitions failed with error %i!\n",__func__, ret);
    return ret;
  }
  return 0;
}

int config_exit(void)
{
  return CONFIG_EXIT_RET;
}
