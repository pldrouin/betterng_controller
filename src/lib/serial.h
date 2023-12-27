#ifndef _SERIAL_
#define _SERIAL_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <termios.h>
#include <pthread.h>

#include <time.h>

#include <sys/select.h>

#include "utils.h"

#define SERIAL_READ_US_TIMEOUT (100000)

typedef struct
{
    int fd;
    fd_set set;
    struct timeval timeout;
} device;

int serial_init(device *sdev, const char *port, const uint32_t baudrate);

int serial_write(device *sdev, const uint8_t* buf, const ssize_t size);

int serial_read(device *sdev, uint8_t* buf, const ssize_t maxsize);

int serial_close(device *sdev);

#endif
