#include "controller_cmd.h"

ssize_t _send_cmd(const int fd, const struct cmd* cmd)
{
  ssize_t nbytes=HOST_CMD_NBYTES(cmd->id);
  ssize_t written=write(fd, cmd, nbytes);
  ssize_t total=written;

  if(written<=0) return written;

  while(nbytes>written) {
    nbytes-=written;
    written=write(fd, ((const uint8_t*)cmd)+total, nbytes);

    if(written<=0) return written;
    total+=written;
  }
  return total;
}

ssize_t recv_cmd(const int fd, struct cmd* cmd)
{
  ssize_t ret=read(fd, cmd, 1);
  ssize_t total=ret;

  if(ret<=0) return ret;

  ssize_t nbytes=DEV_CMD_NBYTES(cmd->id);

  while(nbytes>ret) {
    nbytes-=ret;
    ret=read(fd, ((uint8_t*)cmd)+total, nbytes);

    if(ret<=0) return ret;
    total+=ret;
  }

  if((total==2 && !check_one_byte(cmd)) || (total==3 && !check_two_bytes(cmd)) || (total==4 && !check_three_bytes(cmd))) return -1;
  return total;
}

ssize_t _send_recv_cmd(const int fd, const struct cmd* ocmd, const uint8_t iid, struct cmd* icmd)
{
  for(;;) {
    ssize_t ret=_send_cmd(fd, ocmd);

    if(ret!=HOST_CMD_NBYTES(ocmd->id)) return ret;

    ret=recv_cmd(fd, icmd);

    if(ret==DEV_CMD_NBYTES(icmd->id) && icmd->id==iid) return ret;

    //Need synchronisation
    fprintf(stderr,"%s: Warning: Frame out of sync. Resyncing with device...\n",__func__);

    if(tcflush(fd, TCIOFLUSH) < 0) {
      perror("tcflush serial");
      return errno;
    }

    uint8_t byte=PING_CMD_ID;

    for(;;) {

      while(write(fd, &byte, 1)!=1){}

      if(tcdrain(fd) < 0) {
	perror("tcflush serial");
	return errno;
      }

      if((ret=recv_cmd(fd, icmd))>0 && icmd->id==PING_CMD_ID) break;
    }
    //Synced
    fprintf(stderr,"%s: Resyncing with device was successful\n",__func__);

    if(tcflush(fd, TCIFLUSH) < 0) {
      perror("tcflush serial");
      return errno;
    }
  }

  return 0;
}
