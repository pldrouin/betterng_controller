#include "controller.h"

int main(const int nargs, const char* args[])
{
  int fd;
  speed_t speed=0;

  if(nargs<2) {
    fprintf(stderr,"Usage: %s device [baud_rate]\n",args[0]);
    return 1;
  }

  fprintf(stderr,"Opening '%s'\n",args[1]);
  fd = open(args[1], O_RDWR);

  if(fd < 0) {
    perror("open");
    return 1;
  }

  fcntl(fd, F_SETFL, 0);

  if(nargs>2) {
    uint32_t sbuf;
    sscanf(args[2],"%" PRIu32, &sbuf);

    switch(sbuf) {

      case 9600:
	speed=B9600;
	break;

      case 19200:
	speed=B19200;
	break;

      case 38400:
	speed=B38400;
	break;

      case 57600:
	speed=B57600;
	break;

      case 115200:
	speed=B115200;
	break;

      default:
	fprintf(stderr,"baud rate '%s' is invalid!\n",args[2]);
	return 1;
    }
  }

  struct termios options;
  int rc;

  if((rc = tcgetattr(fd, &options)) < 0) {
    perror("tcgetattr");
    return 1;
  }

  if(speed) cfsetspeed(&options, speed);

  cfmakeraw(&options);
  options.c_cc[VMIN] = 0;
  options.c_cc[VTIME] = 1;

  if((rc = tcsetattr(fd, TCSANOW, &options)) < 0) {
    perror("tcsetattr serial");
    return 1;
  }

  if(tcflush(fd, TCIOFLUSH) < 0) {
    perror("tcflush serial");
    return 1;
  }

  struct cmd ocmd, icmd;
  ssize_t ret;
  build_ping_cmd(&ocmd);

  if((ret=send_recv_cmd(fd, &ocmd, PING_REQ_ID, &icmd))<=0) {
    fprintf(stderr,"send_cmd returned %li!\n",ret);
    return 1;
  }
  printf("Ping succeeded!\n");

  build_reset_cmd(&ocmd);

  if((ret=send_cmd(fd, &ocmd))<=0) {
    fprintf(stderr,"send_cmd returned %li!\n",ret);
    return 1;
  }
  close(fd);

  return 0;
}
