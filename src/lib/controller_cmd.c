#include "controller_cmd.h"

int send_receive_get_fan_rpm_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* rpm)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_RPM_CMD_REQ_ID, {id}, 1},{GET_FAN_RPM_CMD_RESP_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  *rpm=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_fan_voltage_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* voltage)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_VOLTAGE_CMD_REQ_ID, {id}, 1},{GET_FAN_VOLTAGE_CMD_RESP_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  *voltage=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_get_fan_voltage_target_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* voltage)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_VOLTAGE_TARGET_CMD_REQ_ID, {id}, 1},{GET_FAN_VOLTAGE_TARGET_CMD_RESP_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  *voltage=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  return 0;
}

int send_receive_fan_adc_calibration_cmd(sl_device *sl_dev, const uint8_t id)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{FAN_ADC_CALIBRATION_CMD_REQ_ID, {id}, 1},{ACK_CMD_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_switch_fan_control_cmd(sl_device *sl_dev, const uint8_t id, const uint8_t mode)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SWITCH_FAN_CONTROL_CMD_REQ_ID, {id, mode}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_output_cmd(sl_device *sl_dev, const uint8_t id, uint8_t* output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_OUTPUT_CMD_REQ_ID, {id}, 1},{GET_FAN_OUTPUT_CMD_RESP_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  *output=rr.resp.bytes[0];
  return 0;
}

int send_receive_set_fan_output_cmd(sl_device *sl_dev, const uint8_t id, const uint8_t output)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_OUTPUT_CMD_REQ_ID, {id, output}, 2},{ACK_CMD_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}

int send_receive_get_fan_voltage_response_cmd(sl_device *sl_dev, const uint8_t id, uint16_t* v_no_out, uint16_t* dvdout, int16_t* d2vdout2)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{GET_FAN_VOLTAGE_RESPONSE_CMD_REQ_ID, {id}, 1},{GET_FAN_VOLTAGE_RESPONSE_CMD_RESP_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  *v_no_out=be16toh(*(uint16_t*)&rr.resp.bytes[0]);
  *dvdout=be16toh(*(uint16_t*)&rr.resp.bytes[2]);
  *d2vdout2=(int16_t)be16toh(*(int16_t*)&rr.resp.bytes[4]);
  return 0;
}

int send_receive_set_fan_voltage_response_cmd(sl_device *sl_dev, const uint8_t id, const uint16_t vnoout, const uint16_t dvdout, const int16_t d2vdout2)
{
  CHECK_FAN_ID(id);
  struct req_resp rr={{SET_FAN_VOLTAGE_RESPONSE_CMD_REQ_ID, {id, (uint8_t)(vnoout>>8), (uint8_t)vnoout, (uint8_t)(dvdout>>8), (uint8_t)dvdout, (uint8_t)(d2vdout2>>8), (uint8_t)d2vdout2}, 7},{ACK_CMD_ID}};
  int ret=send_recv_cmd(sl_dev, &rr);

  if(ret) return ret;
  CHECK_ACK_REPLY(rr);
  return 0;
}
