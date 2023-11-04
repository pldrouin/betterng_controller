#ifndef _CONTROLLER_CMD_
#define _CONTROLLER_CMD_

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include "serial_link.h"

static inline int send_receive_ping_cmd(sl_device *sl_dev, struct req_resp* rr){return send_recv_one_byte_cmd(sl_dev, PING_CMD_ID, PING_CMD_ID, rr);}

#endif
