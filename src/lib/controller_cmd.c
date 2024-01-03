#include "controller_cmd.h"

int send_receive_get_lm75a_temp_sensor_list_cmd(uint8_t* const list)
{
  struct req_resp rr={{GET_LM75A_TEMP_SENSOR_LIST_CMD_REQ_ID, {}, 0},{GET_LM75A_TEMP_SENSOR_LIST_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *list=rr.resp.bytes[0];
  return 0;
}

int send_receive_add_lm75a_temp_sensor_cmd(const uint8_t id)
{
  struct req_resp rr={{ADD_LM75A_TEMP_SENSOR_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_lm75a_temp_sensor_cmd(const uint8_t id)
{
  struct req_resp rr={{DEL_LM75A_TEMP_SENSOR_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_analog_temp_sensor_list_cmd(uint8_t* const list)
{
  struct req_resp rr={{GET_ANALOG_TEMP_SENSOR_LIST_CMD_REQ_ID, {}, 0},{GET_ANALOG_TEMP_SENSOR_LIST_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *list=rr.resp.bytes[0];
  return 0;
}

int send_receive_add_analog_temp_sensor_cmd(const uint8_t id)
{
  struct req_resp rr={{ADD_ANALOG_TEMP_SENSOR_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_analog_temp_sensor_cmd(const uint8_t id)
{
  struct req_resp rr={{DEL_ANALOG_TEMP_SENSOR_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_analog_temp_sensor_adc_value_cmd(const uint8_t id, uint16_t* const adc_value)
{
  struct req_resp rr={{GET_ANALOG_TEMP_SENSOR_ADC_VALUE_CMD_REQ_ID, {id}, 1},{GET_ANALOG_TEMP_SENSOR_ADC_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *adc_value=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_lm75a_temp_sensor_value_cmd(const uint8_t id, int16_t* const value)
{
  struct req_resp rr={{GET_LM75A_TEMP_SENSOR_VALUE_CMD_REQ_ID, {id}, 1},{GET_LM75A_TEMP_SENSOR_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *value=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_analog_temp_sensor_value_cmd(const uint8_t id, int16_t* const value)
{
  struct req_resp rr={{GET_ANALOG_TEMP_SENSOR_VALUE_CMD_REQ_ID, {id}, 1},{GET_ANALOG_TEMP_SENSOR_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *value=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_soft_temp_sensor_value_cmd(const uint8_t id, int16_t* const value)
{
  struct req_resp rr={{GET_SOFT_TEMP_SENSOR_VALUE_CMD_REQ_ID, {id}, 1},{GET_SOFT_TEMP_SENSOR_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *value=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_lm75a_temp_sensor_calib_cmd(const uint8_t id, int16_t* a0, int16_t* a1, int16_t* a2)
{
  struct req_resp rr={{GET_LM75A_TEMP_SENSOR_CALIB_CMD_REQ_ID, {id}, 1},{GET_LM75A_TEMP_SENSOR_CALIB_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *a0=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *a1=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[2]);
  *a2=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[4]);
  return 0;
}

int send_receive_get_analog_temp_sensor_calib0_cmd(const uint8_t id, float* a0, float* a1)
{
  struct req_resp rr={{GET_ANALOG_TEMP_SENSOR_CALIB0_CMD_REQ_ID, {id}, 1},{GET_ANALOG_TEMP_SENSOR_CALIB0_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  uint32_t i32=be32toh(*(uint32_t*)&rr.resp.bytes[0]);
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
  *a0=*(float*)&i32;
  i32=be32toh(*(uint32_t*)&rr.resp.bytes[4]);
  *a1=*(float*)&i32;
  #pragma GCC diagnostic pop
  return 0;
}

int send_receive_get_analog_temp_sensor_calib1_cmd(const uint8_t id, float* a2, int16_t* shift)
{
  struct req_resp rr={{GET_ANALOG_TEMP_SENSOR_CALIB1_CMD_REQ_ID, {id}, 1},{GET_ANALOG_TEMP_SENSOR_CALIB1_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
  uint32_t i32=be32toh(*(uint32_t*)&rr.resp.bytes[0]);
  *a2=*(float*)&i32;
  #pragma GCC diagnostic pop
  *shift=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[4]);
  return 0;
}

int send_receive_set_lm75a_temp_sensor_calib_cmd(const uint8_t id, const int16_t a0, const int16_t a1, const int16_t a2)
{
  struct req_resp rr={{SET_LM75A_TEMP_SENSOR_CALIB_CMD_REQ_ID, {id, (uint8_t)(a0>>8), (uint8_t)a0, (uint8_t)(a1>>8), (uint8_t)a1, (uint8_t)(a2>>8), (uint8_t)a2}, 7},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_set_analog_temp_sensor_calib0_cmd(const uint8_t id, const float a0, const float a1)
{
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
  uint32_t ua0=*(uint32_t*)&a0;
  uint32_t ua1=*(uint32_t*)&a1;
  #pragma GCC diagnostic pop
  struct req_resp rr={{SET_ANALOG_TEMP_SENSOR_CALIB0_CMD_REQ_ID, {id, (uint8_t)(ua0>>24), (uint8_t)(ua0>>16), (uint8_t)(ua0>>8), (uint8_t)ua0, (uint8_t)(ua1>>24), (uint8_t)(ua1>>16), (uint8_t)(ua1>>8), (uint8_t)ua1}, 9},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_set_analog_temp_sensor_calib1_cmd(const uint8_t id, const float a2, const int16_t shift)
{
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
  uint32_t ua2=*(uint32_t*)&a2;
  #pragma GCC diagnostic pop
  struct req_resp rr={{SET_ANALOG_TEMP_SENSOR_CALIB1_CMD_REQ_ID, {id, (uint8_t)(ua2>>24), (uint8_t)(ua2>>16), (uint8_t)(ua2>>8), (uint8_t)ua2, (uint8_t)(shift>>8), (uint8_t)shift}, 7},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_set_soft_temp_sensor_value_cmd(const uint8_t id, const int16_t value)
{
  struct req_resp rr={{SET_SOFT_TEMP_SENSOR_VALUE_CMD_REQ_ID, {id, (uint8_t)(value>>8), (uint8_t)value}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_lm75a_temp_sensor_alarm_value_cmd(const uint8_t id, int16_t* const alarm_value)
{
  struct req_resp rr={{GET_LM75A_TEMP_SENSOR_ALARM_VALUE_CMD_REQ_ID, {id}, 1},{GET_LM75A_TEMP_SENSOR_ALARM_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *alarm_value=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_analog_temp_sensor_alarm_value_cmd(const uint8_t id, int16_t* const alarm_value)
{
  struct req_resp rr={{GET_ANALOG_TEMP_SENSOR_ALARM_VALUE_CMD_REQ_ID, {id}, 1},{GET_ANALOG_TEMP_SENSOR_ALARM_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *alarm_value=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_soft_temp_sensor_alarm_value_cmd(const uint8_t id, int16_t* const alarm_value)
{
  struct req_resp rr={{GET_SOFT_TEMP_SENSOR_ALARM_VALUE_CMD_REQ_ID, {id}, 1},{GET_SOFT_TEMP_SENSOR_ALARM_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *alarm_value=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_set_lm75a_temp_sensor_alarm_value_cmd(const uint8_t id, const int16_t alarm_value)
{
  struct req_resp rr={{SET_LM75A_TEMP_SENSOR_ALARM_VALUE_CMD_REQ_ID, {id, (uint8_t)(alarm_value>>8), (uint8_t)alarm_value}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_set_analog_temp_sensor_alarm_value_cmd(const uint8_t id, const int16_t alarm_value)
{
  struct req_resp rr={{SET_ANALOG_TEMP_SENSOR_ALARM_VALUE_CMD_REQ_ID, {id, (uint8_t)(alarm_value>>8), (uint8_t)alarm_value}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_set_soft_temp_sensor_alarm_value_cmd(const uint8_t id, const int16_t alarm_value)
{
  struct req_resp rr={{SET_SOFT_TEMP_SENSOR_ALARM_VALUE_CMD_REQ_ID, {id, (uint8_t)(alarm_value>>8), (uint8_t)alarm_value}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_list_cmd(uint8_t* const list)
{
  struct req_resp rr={{GET_FAN_LIST_CMD_REQ_ID, {}, 0},{GET_FAN_LIST_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *list=rr.resp.bytes[0];
  return 0;
}

int send_receive_add_fan_cmd(const uint8_t id)
{
  struct req_resp rr={{ADD_FAN_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_fan_cmd(const uint8_t id)
{
  struct req_resp rr={{DEL_FAN_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_lm75a_temp_sensor_list_cmd(const uint8_t fan_id, uint8_t* const list)
{
  struct req_resp rr={{GET_FAN_LM75A_TEMP_SENSOR_LIST_CMD_REQ_ID, {fan_id}, 1},{GET_FAN_LM75A_TEMP_SENSOR_LIST_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *list=rr.resp.bytes[0];
  return 0;
}

int send_receive_get_fan_analog_temp_sensor_list_cmd(const uint8_t fan_id, uint8_t* const list)
{
  struct req_resp rr={{GET_FAN_ANALOG_TEMP_SENSOR_LIST_CMD_REQ_ID, {fan_id}, 1},{GET_FAN_ANALOG_TEMP_SENSOR_LIST_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *list=rr.resp.bytes[0];
  return 0;
}

int send_receive_get_fan_soft_temp_sensor_list_cmd(const uint8_t fan_id, uint8_t* const list)
{
  struct req_resp rr={{GET_FAN_SOFT_TEMP_SENSOR_LIST_CMD_REQ_ID, {fan_id}, 1},{GET_FAN_SOFT_TEMP_SENSOR_LIST_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *list=rr.resp.bytes[0];
  return 0;
}

int send_receive_add_fan_lm75a_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id)
{
  struct req_resp rr={{ADD_FAN_LM75A_TEMP_SENSOR_CMD_REQ_ID, {fan_id, sens_id}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_add_fan_analog_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id)
{
  struct req_resp rr={{ADD_FAN_ANALOG_TEMP_SENSOR_CMD_REQ_ID, {fan_id, sens_id}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_add_fan_soft_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id)
{
  struct req_resp rr={{ADD_FAN_SOFT_TEMP_SENSOR_CMD_REQ_ID, {fan_id, sens_id}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_fan_lm75a_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id)
{
  struct req_resp rr={{DEL_FAN_LM75A_TEMP_SENSOR_CMD_REQ_ID, {fan_id, sens_id}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_fan_analog_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id)
{
  struct req_resp rr={{DEL_FAN_ANALOG_TEMP_SENSOR_CMD_REQ_ID, {fan_id, sens_id}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_fan_soft_temp_sensor_cmd(const uint8_t fan_id, const uint8_t sens_id)
{
  struct req_resp rr={{DEL_FAN_SOFT_TEMP_SENSOR_CMD_REQ_ID, {fan_id, sens_id}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_add_fan_curve_point_cmd(const uint8_t fan_id, const int8_t temp, const uint8_t output)
{
  struct req_resp rr={{ADD_FAN_CURVE_POINT_CMD_REQ_ID, {fan_id, (uint8_t)temp, output}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_del_fan_curve_point_cmd(const uint8_t fan_id, const uint8_t index)
{
  struct req_resp rr={{DEL_FAN_CURVE_POINT_CMD_REQ_ID, {fan_id, index}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_n_curve_points_cmd(const uint8_t fan_id, uint8_t* const ncurvepoints)
{
  struct req_resp rr={{GET_FAN_N_CURVE_POINTS_CMD_REQ_ID, {fan_id}, 1},{GET_FAN_N_CURVE_POINTS_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *ncurvepoints=rr.resp.bytes[0];
  return 0;
}

int send_receive_get_fan_curve_point_cmd(const uint8_t fan_id, const uint8_t index, int8_t* const temp, uint8_t* const output)
{
  struct req_resp rr={{GET_FAN_CURVE_POINT_CMD_REQ_ID, {fan_id, index}, 2},{GET_FAN_CURVE_POINT_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  if(rr.resp.bytes[2]) return (int8_t)rr.resp.bytes[2];
  *temp=(int8_t)rr.resp.bytes[0];
  *output=rr.resp.bytes[1];
  return 0;
}

int send_receive_get_fan_hysterisis_cmd(const uint8_t id, uint8_t* const hysterisis)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_HYSTERISIS_CMD_REQ_ID, {id}, 1},{GET_FAN_HYSTERISIS_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *hysterisis=rr.resp.bytes[0];
  return 0;
}

int send_receive_set_fan_hysterisis_cmd(const uint8_t id, const uint8_t hysterisis)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_HYSTERISIS_CMD_REQ_ID, {id, hysterisis}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_max_rpm_cmd(const uint8_t id, int16_t* const max_rpm)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_MIN_TACH_TICKS_CMD_REQ_ID, {id}, 1},{GET_FAN_MIN_TACH_TICKS_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  int16_t min_tach_ticks=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *max_rpm = (abs(min_tach_ticks)==0?INT16_MAX:convert_fan_rpm(min_tach_ticks));
  return 0;
}

int send_receive_set_fan_max_rpm_cmd(const uint8_t id, const int16_t max_rpm)
{
  const int16_t min_tach_ticks = (max_rpm==INT16_MAX?0:convert_fan_ticks(max_rpm));
  struct req_resp rr={{SET_FAN_MIN_TACH_TICKS_CMD_REQ_ID, {id, (uint8_t)(min_tach_ticks>>8), (uint8_t)(min_tach_ticks)}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_min_rpm_cmd(const uint8_t id, int16_t* const min_rpm)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_MAX_TACH_TICKS_CMD_REQ_ID, {id}, 1},{GET_FAN_MAX_TACH_TICKS_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  int16_t min_tach_ticks=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *min_rpm = (abs(min_tach_ticks)==0?INT16_MAX:convert_fan_rpm(min_tach_ticks));
  return 0;
}

int send_receive_set_fan_min_rpm_cmd(const uint8_t id, const int16_t min_rpm)
{
  const int16_t min_tach_ticks = (min_rpm==INT16_MAX?0:convert_fan_ticks(min_rpm));
  struct req_resp rr={{SET_FAN_MAX_TACH_TICKS_CMD_REQ_ID, {id, (uint8_t)(min_tach_ticks>>8), (uint8_t)(min_tach_ticks)}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_rpm_cmd(const uint8_t id, int16_t* const rpm)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_TACH_TICKS_CMD_REQ_ID, {id}, 1},{GET_FAN_TACH_TICKS_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  int16_t tach_ticks=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *rpm = (abs(tach_ticks)==INT16_MAX?0:convert_fan_rpm(tach_ticks));
  return 0;
}

int send_receive_get_fan_mode_cmd(const uint8_t id, uint8_t* const mode)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_MODE_CMD_REQ_ID, {id}, 1},{GET_FAN_MODE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *mode=rr.resp.bytes[0];
  return 0;
}

int send_receive_switch_fan_mode_cmd(const uint8_t id, const uint8_t mode)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SWITCH_FAN_MODE_CMD_REQ_ID, {id, mode}, 2},{ACK_CMD_ID}};
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

int send_receive_get_fan_adc_value_cmd(const uint8_t id, uint16_t* const adc_value)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_ADC_VALUE_CMD_REQ_ID, {id}, 1},{GET_FAN_ADC_VALUE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *adc_value=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
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

int send_receive_set_fan_output_auto_cmd(const uint8_t id, const uint8_t output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_OUTPUT_AUTO_CMD_REQ_ID, {id, output}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_duty_cycle_response_cmd(const uint8_t id, uint16_t* const dc_no_out, int16_t* const ddcdout, int16_t* const d2dcdout2)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_DUTY_CYCLE_RESPONSE_CMD_REQ_ID, {id}, 1},{GET_FAN_DUTY_CYCLE_RESPONSE_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *dc_no_out=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *ddcdout=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[2]);
  *d2dcdout2=(int16_t)be16toh(*(uint16_t*)&rr.resp.bytes[4]);
  return 0;
}

int send_receive_set_fan_duty_cycle_response_cmd(const uint8_t id, uint16_t dc_no_out, const int16_t ddcdout)
{
  CHECK_FAN_ID(id);
  const int16_t d2dcdout2 = calc_d2dcdout2(dc_no_out, ddcdout);
  dc_no_out = calc_dcnoout(ddcdout, d2dcdout2);
  struct req_resp rr={{SET_FAN_DUTY_CYCLE_RESPONSE_CMD_REQ_ID, {id, (uint8_t)(dc_no_out>>8), (uint8_t)dc_no_out, (uint8_t)(ddcdout>>8), (uint8_t)ddcdout, (uint8_t)(d2dcdout2>>8), (uint8_t)d2dcdout2}, 7},{ACK_CMD_ID}};
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

int send_receive_set_fan_voltage_response_cmd(const uint8_t id, const uint16_t v_no_out, const int16_t dvdout)
{
  CHECK_FAN_ID(id);
  const int16_t d2vdout2 = calc_d2vdout2(v_no_out, dvdout);
  struct req_resp rr={{SET_FAN_VOLTAGE_RESPONSE_CMD_REQ_ID, {id, (uint8_t)(v_no_out>>8), (uint8_t)v_no_out, (uint8_t)(dvdout>>8), (uint8_t)dvdout, (uint8_t)(d2vdout2>>8), (uint8_t)d2vdout2}, 7},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_mode_transitions_cmd(const uint8_t id, uint8_t* const pwm_to_voltage_output, uint8_t* const voltage_to_pwm_output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_MODE_TRANSITIONS_CMD_REQ_ID, {id}, 1},{GET_FAN_MODE_TRANSITIONS_CMD_RESP_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  *pwm_to_voltage_output = rr.resp.bytes[0];
  *voltage_to_pwm_output = rr.resp.bytes[1];
  return 0;
}

int send_receive_set_fan_mode_transitions_cmd(const uint8_t id, const uint8_t pwm_to_voltage_output, const uint8_t voltage_to_pwm_output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_MODE_TRANSITIONS_CMD_REQ_ID, {id, pwm_to_voltage_output, voltage_to_pwm_output}, 3},{ACK_CMD_ID}};
  int ret=send_recv_cmd(&gGlobals.sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int calibrate_fan_voltage_response_cmd(const uint8_t id, const uint8_t low_proportional_output, uint8_t mid_proportional_output)
{
  CHECK_FAN_ID(id);

  if(mid_proportional_output > 0) {

    if(mid_proportional_output <= low_proportional_output) {
      fprintf(stderr,"%s: Error: mid_proportional_output value must be larger than low_proportional_output!\n",__func__);
      return -1;
    }

  } else mid_proportional_output=round(0.5*(low_proportional_output+UINT8_MAX));
  uint8_t init_output;

  //Check if fan is active
  printf("Get fan list\n");
  uint8_t list;
  int ret=send_receive_get_fan_list_cmd(&list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan list failed!\n",__func__);
    return ret;
  }

  if(!(list&(1<<id))) {
    fprintf(stderr,"%s: Error: Fan %u is not currently active!\n",__func__,id);
    return -1;
  }

  //Get initial fan output
  printf("Get initial fan %u output...\n",id);
  ret=send_receive_get_fan_output_cmd(id, &init_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u output failed!\n",__func__,id);
    return ret;
  }

  //Turn fan to max output
  printf("Turning fan %u to max output...\n",id);
  ret=send_receive_set_fan_output_cmd(id, UINT8_MAX);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u output failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Switch fan to PWM mode as it is the only way to reach the maximum voltage
  printf("Switching fan %u to PWM mode...\n",id);
  ret=send_receive_switch_fan_mode_cmd(id, FAN_PWM_MODE);

  if(ret) {
    fprintf(stderr,"%s: Error: Switch fan %u control mode failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Change fan calibration to simple proportional response
  printf("Changing fan %u voltage response to simple proportional response...\n",id);
  ret=send_receive_set_fan_proportional_voltage_response_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u voltage response failed!\n",__func__,id);
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

  //Switch fan to voltage mode
  printf("Switching fan %u to voltage mode...\n",id);
  ret=send_receive_switch_fan_mode_cmd(id, FAN_VOLTAGE_MODE);

  if(ret) {
    fprintf(stderr,"%s: Error: Switch fan %u control mode failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Turn fan to mid voltage
  printf("Turning fan %u to mid voltage...\n",id);
  const double mid_voltage = (double)((int16_t)(((int32_t)FAN_OFF_LEVEL_DEFAULT_VALUE * (int16_t)((((int32_t)mid_proportional_output)*FAN_CORRECTED_MAX_VOLTAGE_SCALE)>>8)) >> FAN_MAX_VOLTAGE_SCALE_SHIFT)) * FAN_MAX_VOLTAGE_SCALE / FAN_OFF_LEVEL_DEFAULT_VALUE;
  ret=send_receive_set_fan_output_cmd(id, mid_proportional_output);

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
  const double low_voltage = (double)((int16_t)(((int32_t)FAN_OFF_LEVEL_DEFAULT_VALUE * (int16_t)((((int32_t)low_proportional_output)*FAN_CORRECTED_MAX_VOLTAGE_SCALE)>>8)) >> FAN_MAX_VOLTAGE_SCALE_SHIFT)) * FAN_MAX_VOLTAGE_SCALE / FAN_OFF_LEVEL_DEFAULT_VALUE;
  ret=send_receive_set_fan_output_cmd(id, low_proportional_output);

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
  printf("max_rpm %f, mid_rpm is %f, low_rpm is %f\n", max_rpm, mid_rpm, low_rpm);
  printf("mid_output is %f, low_output is %f\n", mid_output, low_output);
  printf("mid_voltage is %f, low_voltage is %f\n", mid_voltage, low_voltage);

  const double mid_a = ((uint16_t)UINT8_MAX)*UINT8_MAX-mid_output*mid_output;
  const double mid_b = mid_output*(UINT8_MAX-mid_output);
  const double mid_c = mid_voltage*((uint16_t)UINT8_MAX)*UINT8_MAX - (double)FAN_MAX_VOLTAGE_SCALE*mid_output*mid_output;
  const double low_a = ((uint16_t)UINT8_MAX)*UINT8_MAX-low_output*low_output;
  const double low_b = low_output*(UINT8_MAX-low_output);
  const double low_c = low_voltage*((uint16_t)UINT8_MAX)*UINT8_MAX - (double)FAN_MAX_VOLTAGE_SCALE*low_output*low_output;
  //printf("Matrix is\n%f\t%f\n%f\t%f\n",mid_a,mid_b,low_a,low_b);

  const double det=mid_a*low_b-mid_b*low_a;
  const double dvnoout = (low_b*mid_c-mid_b*low_c)/det;
  const double ddvdout = ((-low_a*mid_c+mid_a*low_c)/det)*256./UINT8_MAX;
  const uint16_t vnoout = round(dvnoout);
  const int16_t dvdout = round(ddvdout);
  //printf("Inverse matrix is\n%f\t%f\n%f\t%f\n",low_b/det,-mid_b/det,-low_a/det,mid_a/det);
  printf("vnoout is %f, dvdout is %f, d2vdout2 is %f\n",dvnoout,ddvdout,(FAN_MAX_VOLTAGE_SCALE-dvnoout-(ddvdout*UINT8_MAX)/256.)*65536./65025);
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

int calibrate_fan_duty_cycle_response_cmd(const uint8_t id, const uint8_t low_duty_cycle, uint8_t mid_duty_cycle)
{
  CHECK_FAN_ID(id);

  if(mid_duty_cycle>0) {

    if(mid_duty_cycle <= low_duty_cycle) {
      fprintf(stderr,"%s: Error: mid_duty_cycle value must be larger than low_duty_cycle!\n",__func__);
      return -1;
    }

  } else mid_duty_cycle = round(0.5*(low_duty_cycle+UINT8_MAX));
  uint8_t init_output;

  //Check if fan is active
  printf("Get fan list\n");
  uint8_t list;
  int ret=send_receive_get_fan_list_cmd(&list);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan list failed!\n",__func__);
    return ret;
  }

  if(!(list&(1<<id))) {
    fprintf(stderr,"%s: Error: Fan %u is not currently active!\n",__func__,id);
    return -1;
  }

  //Get initial fan output
  printf("Get initial fan %u output...\n",id);
  ret=send_receive_get_fan_output_cmd(id, &init_output);

  if(ret) {
    fprintf(stderr,"%s: Error: Get fan %u output failed!\n",__func__,id);
    return ret;
  }

  //Turn fan to max output
  printf("Turning fan %u to max output...\n",id);
  ret=send_receive_set_fan_output_cmd(id, UINT8_MAX);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u output failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Switch fan to PWM mode as it is the only way to reach the maximum voltage
  printf("Switching fan %u to PWM mode...\n",id);
  ret=send_receive_switch_fan_mode_cmd(id, FAN_PWM_MODE);

  if(ret) {
    fprintf(stderr,"%s: Error: Switch fan %u control mode failed!\n",__func__,id);
    goto resume_fan_output;
  }

  //Change fan calibration to simple proportional response
  printf("Changing fan %u response to simple proportional response...\n",id);
  ret=send_receive_set_fan_proportional_duty_cycle_response_cmd(id);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u duty cycle response failed!\n",__func__,id);
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

  //Turn fan to mid output
  printf("Turning fan %u to mid output...\n",id);
  ret=send_receive_set_fan_output_cmd(id, mid_duty_cycle);

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

  //Turn fan to low output
  printf("Turning fan %u to low output...\n",id);
  ret=send_receive_set_fan_output_cmd(id, low_duty_cycle);

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
  printf("max_rpm %f, mid_rpm is %f, low_rpm is %f\n", max_rpm, mid_rpm, low_rpm);
  printf("mid_output is %f, low_output is %f\n", mid_output, low_output);
  printf("mid_duty_cycle is %u, low_duty_cycle is %u\n", mid_duty_cycle, low_duty_cycle);

  const double mid_a = ((uint16_t)UINT8_MAX)*UINT8_MAX-mid_output*mid_output;
  const double mid_b = mid_output*(UINT8_MAX-mid_output);
  const double mid_c = (double)mid_duty_cycle*((uint16_t)UINT8_MAX)*UINT8_MAX - (double)UINT8_MAX*mid_output*mid_output;
  const double low_a = ((uint16_t)UINT8_MAX)*UINT8_MAX-low_output*low_output;
  const double low_b = low_output*(UINT8_MAX-low_output);
  const double low_c = (double)low_duty_cycle*((uint16_t)UINT8_MAX)*UINT8_MAX - (double)UINT8_MAX*low_output*low_output;
  //printf("Matrix is\n%f\t%f\n%f\t%f\n",mid_a,mid_b,low_a,low_b);

  const double det=mid_a*low_b-mid_b*low_a;
  const double ddcnoout = (low_b*mid_c-mid_b*low_c)*64/det;
  const double dddcdout = (-low_a*mid_c+mid_a*low_c)*64/det*256./UINT8_MAX;
  const uint16_t dcnoout = round(ddcnoout);
  const int16_t ddcdout = round(dddcdout);
  //printf("Inverse matrix is\n%f\t%f\n%f\t%f\n",low_b/det,-mid_b/det,-low_a/det,mid_a/det);
  printf("dcnoout is %f /64, ddcdout is %f /64, d2dcdout2 is %f /64\n",ddcnoout,dddcdout,(UINT8_MAX*64-ddcnoout-(dddcdout*UINT8_MAX)/256.)*65536./65025);
  //printf("%f vs %f\n",(mid_a*ddcnoout+mid_b*dddcdout)/64,mid_c);
  //printf("%f vs %f\n",(low_a*ddcnoout+low_b*dddcdout)/64,low_c);
  
  //Update fan duty cycle response
  printf("Updating fan %u duty cycle response...\n",id);
  ret=send_receive_set_fan_duty_cycle_response_cmd(id, dcnoout, ddcdout);

  if(ret) {
    fprintf(stderr,"%s: Error: Set fan %u duty cycle response failed!\n",__func__,id);
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
  int16_t prev_rpm=0, cur_rpm;
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

int _get_fan_rpm(const uint8_t id, const int16_t prev_rpm, int16_t* const rpm)
{
  int ret;

  //do {
    ret=send_receive_get_fan_rpm_cmd(id, rpm);

    if(ret) {
      fprintf(stderr,"%s: Error: Get fan rpm failed!\n",__func__);
      return ret;
    }

  //} while(*rpm==prev_rpm);
  *rpm=abs(*rpm);
  return 0;
}

