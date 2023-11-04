#include "serial.h"

#define DEBUG_PRINT printf
#define printtime printtime
//#define DEBUG_PRINT(...)
//#define printtime(...)
//#define DEBUG_PRINT2 printf
#define DEBUG_PRINT2(...)

int serial_init(device *sdev, const char *port, const uint32_t baudrate)
{
  struct termios tio;

  sdev->fd = open(port, O_RDWR|O_NOCTTY);//| O_NONBLOCK);
  if ((sdev->fd)<0)
  {
    fprintf(stderr, "%s: Error: Failed to open device %s: %s \n",__func__, port, strerror(errno));
    return (sdev->fd);
  }

  memset(&tio,0,sizeof(tio));
  tio.c_iflag = IGNBRK | IGNPAR;
  tio.c_oflag &= ~(OPOST|OLCUC|ONLCR|OCRNL|ONOCR|ONLRET);
  tio.c_cflag |= CS8|CREAD|CLOCAL|HUPCL;
  tio.c_lflag &= ~(ISIG|ICANON|ECHO|IEXTEN);
  //printf("c_oflag=%u\n",tio.c_oflag);
  //printf("c_lflag=%u\n",tio.c_lflag);
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;

  cfsetospeed(&tio,baudrate);
  cfsetispeed(&tio,baudrate);

  if(tcsetattr(sdev->fd,TCSAFLUSH,&tio)== -1)
  {
    fprintf(stderr, "%s: Error with tcsetattr = %s\n", __func__, strerror(errno));
    return(-1);
  }
  tcflush(sdev->fd, TCIFLUSH);
  return (sdev->fd);
}

int serial_write(device *sdev, const uint8_t* buf, const ssize_t size)
{
  int ret = write(sdev->fd, buf, size);

  DEBUG_PRINT("Wrote %d:", ret);

  for(int b=0; b<ret; ++b) DEBUG_PRINT(" 0x%x",buf[b]);
  DEBUG_PRINT("\n");

  if(ret<0) perror("write");
  tcdrain(sdev->fd);
  return ret;
}

int serial_read(device *sdev, uint8_t* buf, const ssize_t maxsize)
{
  int ret;
  FD_ZERO(&sdev->set);
  FD_SET(sdev->fd,&sdev->set);

  sdev->timeout.tv_sec = 0;
  sdev->timeout.tv_usec = SERIAL_READ_US_TIMEOUT;

  for(;;) {
    ret = select((sdev->fd)+1,&sdev->set,NULL,NULL,&sdev->timeout);

    if(ret == -1) {
      perror("select");
      return ret;

    } else if(ret == 0) {
      return ret;

    } else {
      ret=read(sdev->fd, buf, maxsize);

      DEBUG_PRINT("Read %d:", ret);

      for(int b=0; b<ret; ++b) DEBUG_PRINT(" 0x%x",buf[b]);
      DEBUG_PRINT("\n");
      return ret;
    }
  }
}

int serial_close(device *sdev)
{
  return close(sdev->fd);
}
