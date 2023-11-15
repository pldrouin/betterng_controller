#include "controller_cmd.h"

int send_receive_get_fan_rpm_cmd(const uint8_t id, uint16_t* const rpm)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_RPM_CMD_REQ_ID, {id}, 1},{GET_FAN_RPM_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *rpm=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_fan_off_level_cmd(const uint8_t id, int16_t* const off_level)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_OFF_LEVEL_CMD_REQ_ID, {id}, 1},{GET_FAN_OFF_LEVEL_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *off_level=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_fan_voltage_cmd(const uint8_t id, uint16_t* const voltage)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_VOLTAGE_CMD_REQ_ID, {id}, 1},{GET_FAN_VOLTAGE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *voltage=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_fan_voltage_target_cmd(const uint8_t id, uint16_t* const voltage)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_VOLTAGE_TARGET_CMD_REQ_ID, {id}, 1},{GET_FAN_VOLTAGE_TARGET_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *voltage=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_fan_adc_calibration_cmd(const uint8_t id)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{FAN_ADC_CALIBRATION_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_switch_fan_control_cmd(const uint8_t id, const uint8_t mode)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SWITCH_FAN_CONTROL_CMD_REQ_ID, {id, mode}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_output_cmd(const uint8_t id, uint8_t* const output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_OUTPUT_CMD_REQ_ID, {id}, 1},{GET_FAN_OUTPUT_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *output=rr.resp.bytes[0];
  return 0;
}

int send_receive_set_fan_output_cmd(const uint8_t id, const uint8_t output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_OUTPUT_CMD_REQ_ID, {id, output}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_voltage_response_cmd(const uint8_t id, uint16_t* const v_no_out, int16_t* const dvdout, int16_t* const d2vdout2)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_VOLTAGE_RESPONSE_CMD_REQ_ID, {id}, 1},{GET_FAN_VOLTAGE_RESPONSE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *v_no_out=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *dvdout=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[2]);
  *d2vdout2=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[4]);
  return 0;
}

int send_receive_set_fan_voltage_response_cmd(const uint8_t id, const uint16_t vnoout, const int16_t dvdout)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_VOLTAGE_RESPONSE_CMD_REQ_ID, {id, (uint8_t)(vnoout>>8), (uint8_t)vnoout, (uint8_t)(dvdout>>8), (uint8_t)dvdout}, 5},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int calibrate_fan_voltage_response_cmd(const uint8_t id, const uint16_t min_voltage)
{
  CHECK_FAN_ID(id);

  if(min_voltage >= FAN_MAX_VOLTAGE_SCALE) {
    fprintf(stderr,"%s: Error: min_voltage value must be smaller than %u!\n",__func__,FAN_MAX_VOLTAGE_SCALE);
    return -1;
  }
  uint8_t init_output;

  //Get initial fan output
  printf("Get initial fan %u output...\n",id);
  int ret=send_receive_get_fan_output_cmd(id, &init_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u output failed!\n",__func__,id);
    return ret;
  }

  //Turn fan to max voltage
  printf("Turning fan %u to max voltage...\n",id);
  ret=send_receive_set_fan_output_cmd(id, UINT8_MAX);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u output failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Switch fan to voltage mode
  printf("Switching fan %u to voltage mode...\n",id);
  ret=send_receive_switch_fan_control_cmd(id, FAN_VOLTAGE_MODE);

  if(ret) {
    fprintf(stderr,"%s: Error: Switch fan %u control mode failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Change fan calibration to simple proportional response
  printf("Changing fan %u voltage response to simple proportional response...\n",id);
  ret=send_receive_set_fan_voltage_response_cmd(id, 0, FAN_MAX_VOLTAGE_SCALE);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u voltage response failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Get fan off level
  printf("Getting fan %u off level\n",id);
  int16_t off_level;
  ret=send_receive_get_fan_off_level_cmd(id, &off_level);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u off level failed!\n",__func__,id);
    goto resume_fan_output;
  }

  double max_rpm;
  //Get RPM reading at max voltage;
  //sleep(10);
  ret=_get_stable_fan_rpm(id, RPM_READING_N_OSCILLATIONS, &max_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u average RPM measurement failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Turn fan to low voltage
  printf("Turning fan %u to mid voltage...\n",id);
  uint8_t output=round(UINT8_MAX*0.5*((double)min_voltage/FAN_MAX_VOLTAGE_SCALE+1));
  const double mid_voltage = (double)((int16_t)(off_level * ((uint16_t)(output * FAN_MAX_VOLTAGE_SCALE/UINT8_MAX)) / FAN_MAX_VOLTAGE_SCALE)) * FAN_MAX_VOLTAGE_SCALE / off_level;
  ret=send_receive_set_fan_output_cmd(id, output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u output failed!\n",__func__,id);
    goto resume_fan_output;
  }
  double mid_rpm;
  //Get RPM reading at mid voltage;
  //sleep(10);
  ret=_get_stable_fan_rpm(id, RPM_READING_N_OSCILLATIONS, &mid_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u average RPM measurement failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Turn fan to low voltage
  printf("Turning fan %u to low voltage...\n",id);
  output=ceil(UINT8_MAX*(double)min_voltage/FAN_MAX_VOLTAGE_SCALE);
  const double low_voltage = (double)((int16_t)(off_level * ((uint16_t)(output * FAN_MAX_VOLTAGE_SCALE/UINT8_MAX)) / FAN_MAX_VOLTAGE_SCALE)) * FAN_MAX_VOLTAGE_SCALE / off_level;
  ret=send_receive_set_fan_output_cmd(id, output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u output failed!\n",__func__,id);
    goto resume_fan_output;
  }
  double low_rpm;
  //Get RPM reading at low voltage;
  //sleep(10);
  ret=_get_stable_fan_rpm(id, RPM_READING_N_OSCILLATIONS, &low_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u average RPM measurement failed!\n",__func__,id);
    goto resume_fan_output;
  }

  const double mid_output = mid_rpm/max_rpm * UINT8_MAX;
  const double low_output = low_rpm/max_rpm * UINT8_MAX;
  printf("mid_output is %f, low_output is %f\n",mid_output, low_output);
  printf("mid_voltage is %f, low_voltage is %f\n",mid_voltage, low_voltage);

  const double mid_a = ((uint16_t)UINT8_MAX)*UINT8_MAX-mid_output*mid_output;
  const double mid_b = mid_output*(UINT8_MAX-mid_output);
  const double mid_c = mid_voltage*((uint16_t)UINT8_MAX)*UINT8_MAX - (double)FAN_MAX_VOLTAGE_SCALE*mid_output*mid_output;
  const double low_a = ((uint16_t)UINT8_MAX)*UINT8_MAX-low_output*low_output;
  const double low_b = low_output*(UINT8_MAX-low_output);
  const double low_c = low_voltage*((uint16_t)UINT8_MAX)*UINT8_MAX - (double)FAN_MAX_VOLTAGE_SCALE*low_output*low_output;
  //printf("Matrix is\n%f\t%f\n%f\t%f\n",mid_a,mid_b,low_a,low_b);

  const double det=mid_a*low_b-mid_b*low_a;
  const double dvnoout = (low_b*mid_c-mid_b*low_c)/det;
  const double ddvdout = (-low_a*mid_c+mid_a*low_c)/det;
  const uint16_t vnoout = round(dvnoout);
  const int16_t dvdout = round(ddvdout);
  //printf("Inverse matrix is\n%f\t%f\n%f\t%f\n",low_b/det,-mid_b/det,-low_a/det,mid_a/det);
  printf("vnoout is %f, dvdout is %f, d2vdout2 is %f\n",dvnoout,ddvdout,FAN_MAX_VOLTAGE_SCALE-dvnoout-ddvdout);
  //printf("%f vs %f\n",mid_a*dvnoout+mid_b*ddvdout,mid_c);
  //printf("%f vs %f\n",low_a*dvnoout+low_b*ddvdout,low_c);
  
  //Update fan voltage response
  printf("Updating fan %u voltage response...\n",id);
  ret=send_receive_set_fan_voltage_response_cmd(id, vnoout, dvdout);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u voltage response failed!\n",__func__,id);
    goto resume_fan_output;
  }

resume_fan_output:
  printf("Resume fan %u output...\n",id);
  ret=send_receive_set_fan_output_cmd(id, init_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u output failed!\n",__func__,id);
  }
  return ret;
}

int _get_stable_fan_rpm(const uint8_t id, const uint16_t noscillations, double* const average_rpm)
{
  uint16_t o=0;
  uint16_t prev_rpm=0, cur_rpm;
  int ret=_get_fan_rpm(id, prev_rpm, &prev_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan rpm failed!\n",__func__);
    return ret;
  }
  sleep(1);
  ret=_get_fan_rpm(id, prev_rpm, &cur_rpm);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan rpm failed!\n",__func__);
    return ret;
  }

  int8_t rpm_dir=(cur_rpm>prev_rpm?1:(cur_rpm<prev_rpm?-1:0));
  int8_t rpm_low_dir=0, rpm_high_dir=0;
  int8_t last_trend_dir=0;
  uint8_t first_rpm_low=true, first_rpm_high=true;
  uint16_t last_rpm_low=false, last_rpm_high=false;

  do {
    prev_rpm=cur_rpm;
    sleep(1);
    ret=_get_fan_rpm(id, prev_rpm, &cur_rpm);

    if(ret) {
      fprintf(stderr,"%s: Error: Get fan rpm failed!\n",__func__);
      return ret;
    }

    if(cur_rpm>prev_rpm) {

      if(rpm_dir!=1) {
	rpm_dir=1;

	if(first_rpm_low) {
	  last_rpm_low = cur_rpm;
	  first_rpm_low = false;
	  printf("%u \\/ (first)\n",cur_rpm);

	} else {
	  rpm_low_dir = (cur_rpm>last_rpm_low?1:(cur_rpm<last_rpm_low?-1:0));
	  last_rpm_low = cur_rpm;

	  if(!first_rpm_high && !((rpm_high_dir==1 && rpm_low_dir==1 && last_trend_dir==1) || (rpm_high_dir==-1 && rpm_low_dir==-1 && last_trend_dir==-1))) {
	    ++o;
	    *average_rpm += cur_rpm;
	    printf("%u \\/\n",cur_rpm);

	    if(rpm_high_dir==1 && rpm_low_dir==1) last_trend_dir=1;
	    else if(rpm_high_dir==-1 && rpm_low_dir==-1) last_trend_dir=-1;
	    else last_trend_dir=0;

	  } else {
	    o=0;
	    *average_rpm = 0;
	    printf("%u \\/ (discarded)\n",cur_rpm);
	  }
	}

      } else printf("%u /\n",cur_rpm);

    } else if(cur_rpm<prev_rpm) {

      if(rpm_dir!=-1) {
	rpm_dir=-1;

	if(first_rpm_high) {
	  last_rpm_high = cur_rpm;
	  first_rpm_high = false;
	  printf("%u /\\ (first)\n",cur_rpm);
 
	} else {
	  rpm_high_dir = (cur_rpm>last_rpm_high?1:(cur_rpm<last_rpm_high?-1:0));
	  last_rpm_high = cur_rpm;

	  if(!first_rpm_low && !((rpm_low_dir==1 && rpm_high_dir==1 && last_trend_dir==1) || (rpm_low_dir==-1 && rpm_high_dir==-1 && last_trend_dir==-1))) {
	    ++o;
	    *average_rpm += cur_rpm;
	    printf("%u /\\\n",cur_rpm);

	    if(rpm_high_dir==1 && rpm_low_dir==1) last_trend_dir=1;
	    else if(rpm_high_dir==-1 && rpm_low_dir==-1) last_trend_dir=-1;
	    else last_trend_dir=0;

	  } else {
	    o=0;
	    *average_rpm = 0;
	    printf("%u /\\ (discarded)\n",cur_rpm);
	  }
	}

      } else printf("%u \\\n",cur_rpm);
    }

  } while(o<noscillations);
  *average_rpm /= noscillations;
  return 0;
}

int _get_fan_rpm(const uint8_t id, const uint16_t prev_rpm, uint16_t* const rpm)
{
  int ret;

  do {
    ret=send_receive_get_fan_rpm_cmd(id, rpm);

    if(ret) {
      fprintf(stderr,"%s: Error: Get fan rpm failed!\n",__func__);
      return ret;
    }

  } while(*rpm==prev_rpm);
  return 0;
}

