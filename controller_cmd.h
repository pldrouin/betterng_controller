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

struct cmd{
  uint8_t id;
  uint8_t byte1;
  uint8_t byte2;
};

static inline void build_ping_cmd(struct cmd* cmd){cmd->byte1=cmd->id=PING_REQ_ID;}
static inline void build_reset_cmd(struct cmd* cmd){cmd->byte1=cmd->id=RESET_REQ_ID;}

ssize_t send_cmd(const int fd, const struct cmd* cmd);
ssize_t recv_cmd(const int fd, struct cmd* cmd);
ssize_t send_recv_cmd(const int fd, const struct cmd* ocmd, const uint8_t iid, struct cmd* icmd);

#endif
