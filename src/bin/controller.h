#ifndef _CONTROLLER_
#define _CONTROLLER_

#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#define _BSD_SOURCE

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>

#include "serial_link.h"
#include "globals.h"
#include "config.h"
#include "controller_cmd.h"

int main(int nargs, const char* args[]);

#endif
