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

#ifdef __FreeBSD__
#define B500000 500000
#define B1000000 1000000
#endif 

#include "controller_cmd.h"

int main(const int nargs, const char* args[]);

#endif
