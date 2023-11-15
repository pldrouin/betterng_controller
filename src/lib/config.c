#include "config.h"

#define HT_SET_FUNC(func) (ht_set(gGlobals.ht, #func, config_ ## func))

int config()
{
  gGlobals.fptra=NULL;
  gGlobals.fptri=-1;
  gGlobals.parc=0;

  gGlobals.plength=1;

  gGlobals.oout=1; //stdout==1
  gGlobals.eout=2; //stderr==2

  gGlobals.ht=ht_create();
  config_ht_populate();

  gGlobals.oldstdout=dup(1);
  gGlobals.oldstderr=dup(2);

  int (*cfunct)(void);

  while(gGlobals.plength>0) {

    while((gGlobals.plength=getnextparam(gGlobals.fptra,&gGlobals.fptri,false,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf))>0) {
      cfunct=(int (*)(void))ht_get(gGlobals.ht, gGlobals.pbuf);

      if(cfunct) cfunct();

      else {
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
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-result"
    if(gGlobals.fptri!=-1 && gGlobals.fptra[gGlobals.fptri] == stdin) write(gGlobals.oldstderr,"@DONE\n",6);
    #pragma GCC diagnostic pop
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

  free(gGlobals.fptra);
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

  HT_SET_FUNC(get_fan_rpm);
  HT_SET_FUNC(get_fan_off_level);
  HT_SET_FUNC(get_fan_voltage);
  HT_SET_FUNC(get_fan_voltage_target);
  HT_SET_FUNC(fan_adc_calibration);
  HT_SET_FUNC(switch_fan_control);
  HT_SET_FUNC(get_fan_output);
  HT_SET_FUNC(set_fan_output);
  HT_SET_FUNC(get_fan_voltage_response);
  HT_SET_FUNC(set_fan_voltage_response);
  HT_SET_FUNC(calibrate_fan_voltage_response);
}

int config_help(void)
{
  printf(BSTR "config" UBSTR " configuration_file\n"); 
  printf(BSTR "olog" UBSTR " output_log_file\n"); 
  printf(BSTR "elog" UBSTR " error_log_file\n"); 
  printf(BSTR "prompt" UBSTR "\n"); 
  printf(BSTR "get_fan_rpm" UBSTR " fan_id\n"); 
  printf(BSTR "get_fan_off_level" UBSTR " fan_id\n"); 
  printf(BSTR "get_fan_voltage" UBSTR " fan_id\n"); 
  printf(BSTR "get_fan_voltage_target" UBSTR " fan_id\n"); 
  printf(BSTR "fan_adc_calibration" UBSTR " fan_id\n"); 
  printf(BSTR "switch_fan_control" UBSTR " fan_id voltage/pwm/manual\n"); 
  printf(BSTR "get_fan_output" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_output" UBSTR " fan_id 0-255\n"); 
  printf(BSTR "get_fan_voltage_response" UBSTR " fan_id\n"); 
  printf(BSTR "set_fan_voltage_response" UBSTR " fan_id v_no_out dvdout\n"); 
  printf(BSTR "calibrate_fan_voltage_response" UBSTR " fan_id min_voltage\n"); 
  return 0;
}

int config_config(void)
{
  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
    fprintf(stderr,"%s: Error: Missing configuration file name!\n",__func__);
    return -1;
  }

  //If we switch to interactive mode (reading instructions from standard
  //input)
  if(!argsdiffer(gGlobals.pbuf,"-")) {

    if(gGlobals.fptri==-1 || gGlobals.fptra[gGlobals.fptri] != stdin) {
      gGlobals.fptri++;
      gGlobals.fptra=(FILE**)realloc(gGlobals.fptra,(gGlobals.fptri+1)*sizeof(FILE*));
      gGlobals.fptra[gGlobals.fptri]=stdin;
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wunused-result"
      write(gGlobals.oldstderr,"@INTERACTIVE\n",13);
      #pragma GCC diagnostic push
    }

    //Otherwise, if reading from a configuration file
  } else {
    gGlobals.fptri++;
    gGlobals.fptra=(FILE**)realloc(gGlobals.fptra,(gGlobals.fptri+1)*sizeof(FILE*));

    if(!(gGlobals.fptra[gGlobals.fptri]=fopen(gGlobals.pbuf,"r"))) {
      fprintf(stderr,"%s: Error: Cannot open file '%s' in read mode\n",__func__,gGlobals.pbuf);
      ht_destroy(gGlobals.ht);
      return 1;
    }
  }
  return 0;
}

//Output file log, redirecting the standard output
int config_olog(void)
{
  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
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
  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
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

int config_prompt(void)
{
  char* lineptr;
  char* charptr;
  size_t n;
  ssize_t ret;
  int oldnargs=gGlobals.nargs;
  const char** oldargs=gGlobals.args;
  int oldparc=gGlobals.parc;
  gGlobals.nargs=-1;
  gGlobals.parc=-2;
  gGlobals.args=(char const**)&charptr;

  int (*cfunct)(void);

  do {
next_line:
    printf("<bigng> ");
    lineptr=NULL;
    n=0;
    ret=getline(&lineptr, &n, stdin);
    charptr=lineptr;

    if(ret<0) {
      free(lineptr);
      gGlobals.nargs=oldnargs;
      gGlobals.args=oldargs;
      gGlobals.parc=oldparc;
      break;
    }

    do {

      while((gGlobals.plength=getnextparam(gGlobals.fptra,&gGlobals.fptri,false,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf))>0) {
	cfunct=(int (*)(void))ht_get(gGlobals.ht, gGlobals.pbuf);

	if(cfunct) {
	  if(cfunct()==0) goto next_line;

	} else {
	  fprintf(stderr,"%s: Error: Unknown command: '%s'\n",__func__,gGlobals.pbuf);
	  free(lineptr);
	  goto next_line;
	}
      }

      //Assertion: We are ready to perform a task whether a break statement has
      //been reached in the inner loop or plength<=0. Otherwise the value of
      //plength can be assessed and appropriate actions can be taken

      //All the parameters for the current job have been read, the job can now be
      //performed. Do it here

      //If reading argument from the standard input (interactive mode), we
      //indicate that the job is completed through the standard output
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wunused-result"
      if(gGlobals.fptri!=-1 && gGlobals.fptra[gGlobals.fptri] == stdin) write(gGlobals.oldstderr,"@DONE\n",6);
      #pragma GCC diagnostic pop
      fflush(stdout);
      fflush(stderr);
      //Continue reading other commands for the next job

    } while(gGlobals.plength>0);

  } while(charptr == lineptr+ret);
  printf("\n");
  gGlobals.nargs=oldnargs;
  gGlobals.args=oldargs;
  gGlobals.parc=oldparc;
  return 0;
}

int config_ping(void)
{
  int ret=send_receive_ping_cmd();

  if(ret) fprintf(stderr,"%s: Error: Ping failed!\n",__func__);
  return ret;
}

int config_reset(void)
{
  int ret=send_receive_reset_cmd();

  if(ret) fprintf(stderr,"%s: Error: Reset failed!\n",__func__);
  return ret;
}

int config_get_fan_rpm(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t rpm;
  int ret=send_receive_get_fan_rpm_cmd(id, &rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan RPM failed!\n",__func__);
    return ret;
  }
  printf("%u\n", rpm);
  return 0;
}

int config_get_fan_off_level(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int16_t off_level;
  int ret=send_receive_get_fan_off_level_cmd(id, &off_level);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan off_level failed!\n",__func__);
    return ret;
  }
  printf("%i mV\n", off_level);
  return 0;
}

int config_get_fan_voltage(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t voltage;
  int ret=send_receive_get_fan_voltage_cmd(id, &voltage);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan voltage failed!\n",__func__);
    return ret;
  }
  printf("%u mV\n", voltage);
  return 0;
}

int config_get_fan_voltage_target(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t voltage;
  int ret=send_receive_get_fan_voltage_target_cmd(id, &voltage);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan voltage target failed!\n",__func__);
    return ret;
  }
  printf("%u mV\n", voltage);
  return 0;
}

int config_fan_adc_calibration(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  int ret=send_receive_fan_adc_calibration_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Fan ADC calibration request failed!\n",__func__);
    return ret;
  }
  return 0;
}

int config_switch_fan_control(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);

  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
    fprintf(stderr,"%s: Error: Missing fan mode!\n",__func__);
    return -1;
  }
  tolowerstr(gGlobals.pbuf);
  uint8_t mode;

  if(!argsdiffer(gGlobals.pbuf, "voltage")) mode=FAN_VOLTAGE_MODE;

  else if(!argsdiffer(gGlobals.pbuf, "pwm")) mode=FAN_PWM_MODE;

  else if(!argsdiffer(gGlobals.pbuf, "manual")) mode=FAN_MANUAL_MODE;

  else {
    fprintf(stderr, "%s: Error: Fan control mode '%s' is invalid!\n", __func__, gGlobals.pbuf);
    return -1;
  }
  int ret=send_receive_switch_fan_control_cmd(id, mode);

  if(ret) {
    fprintf(stderr,"%s: Error: Switch fan control mode failed!\n",__func__);
    return ret;
  }
  return 0;
}

int config_get_fan_output(void)
{
  uint8_t id;
  uint8_t output;
  CONFIG_GET_FAN_ID(id);

  int ret=send_receive_get_fan_output_cmd(id, &output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan output failed!\n",__func__);
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

  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
    fprintf(stderr,"%s: Error: Missing fan output value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu8, &output);
  int ret=send_receive_set_fan_output_cmd(id, output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan output failed!\n",__func__);
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
    fprintf(stderr,"%s: Error: Get fan voltage response failed!\n",__func__);
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

  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
    fprintf(stderr,"%s: Error: Missing fan v_no_out value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu16, &vnoout);

  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
    fprintf(stderr,"%s: Error: Missing fan dvdout value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNi16, &dvdout);
  int ret=send_receive_set_fan_voltage_response_cmd(id, vnoout, dvdout);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan voltage response failed!\n",__func__);
    return ret;
  }
  return 0;
}

int config_calibrate_fan_voltage_response(void)
{
  uint8_t id;
  CONFIG_GET_FAN_ID(id);
  uint16_t min_voltage;

  if(getnextparam(gGlobals.fptra,&gGlobals.fptri,true,gGlobals.nargs,gGlobals.args,&gGlobals.parc,gGlobals.pbuf)<0) {
    fprintf(stderr,"%s: Error: Missing fan min_voltage value!\n",__func__);
    return -1;
  }
  sscanf(gGlobals.pbuf, "%" SCNu16, &min_voltage);
  int ret=calibrate_fan_voltage_response_cmd(id, min_voltage);

  if(ret) {
    fprintf(stderr,"%s: Error: Calibrate fan voltage response failed!\n",__func__);
    return ret;
  }
  return 0;
}
