#ifndef _CONTROLLER_CMD_
#define _CONTROLLER_CMD_

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>

#define FIRST_TWO_BYTE_CMD_INDEX 255

#define CMD_NBYTES(id) (2+(id>=FIRST_TWO_BYTE_CMD_INDEX))

#define PING_REQ_ID 0
#define PING_RESP_ID 0

#define RESET_REQ_ID 1
#define RESET_RESP_ID 1

struct cmd{
  uint8_t id;
  uint8_t byte1;
  uint8_t byte2;
};

struct req_resp{
  struct cmd req;
  struct cmd resp;
  uint8_t exp_resp_id;
};

#define BUILD_ONE_BYTE_CMD(cmd, ID) ((cmd)->byte1=(cmd)->id=ID ## _REQ_ID)
#define BUILD_TWO_BYTES_CMD(cmd, ID, value) ((cmd)->id=ID ## _REQ_ID; (cmd)->byte1=value; (cmd)->byte2=(cmd)->id+(cmd)->byte1)

static inline void build_ping_cmd(struct cmd* cmd){cmd->byte1=cmd->id=PING_REQ_ID;}
static inline void build_reset_cmd(struct cmd* cmd){cmd->byte1=cmd->id=RESET_REQ_ID;}

ssize_t _send_cmd(const int fd, const struct cmd* cmd);
ssize_t recv_cmd(const int fd, struct cmd* cmd);
ssize_t _send_recv_cmd(const int fd, const struct cmd* ocmd, const uint8_t iid, struct cmd* icmd);

#define send_one_byte_cmd(fd, ID, cmd) ({BUILD_ONE_BYTE_CMD(cmd, ID); _send_cmd(fd, cmd);})
#define send_two_bytes_cmd(fd, ID, value, cmd) ({BUILD_TWO_BYTES_CMD(cmd, ID, value); _send_cmd(fd, cmd);})

#define send_recv_one_byte_cmd(fd, ID, req_resp) ({BUILD_ONE_BYTE_CMD(&(req_resp)->req, ID); _send_recv_cmd(fd, &(req_resp)->req, ID ## _RESP_ID, &(req_resp)->resp);})

#endif
