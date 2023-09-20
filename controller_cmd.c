#include "controller_cmd.h"

static inline bool check_one_byte(const struct cmd* cmd){return (cmd->byte1==cmd->id);}
static inline bool check_two_bytes(const struct cmd* cmd){return (cmd->byte2==cmd->id+cmd->byte1);}

ssize_t send_cmd(const int fd, const struct cmd* cmd)
{
  ssize_t nbytes=CMD_NBYTES(cmd->id);
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

  ssize_t nbytes=CMD_NBYTES(cmd->id);

  while(nbytes>ret) {
    nbytes-=ret;
    ret=read(fd, ((uint8_t*)cmd)+total, nbytes);

    if(ret<=0) return ret;
    total+=ret;
  }

  if((total==2 && !check_one_byte(cmd)) || !check_two_bytes(cmd)) return EIO;
  return total;
}

ssize_t send_recv_cmd(const int fd, const struct cmd* ocmd, const uint8_t iid, struct cmd* icmd)
{
  for(;;) {
    ssize_t ret=send_cmd(fd, ocmd);

    if(ret!=CMD_NBYTES(ocmd->id)) return ret;

    ret=recv_cmd(fd, icmd);

    if(ret==CMD_NBYTES(icmd->id) && icmd->id==iid) return ret;

    //Need synchronisation

    if(tcflush(fd, TCIOFLUSH) < 0) {
      perror("tcflush serial");
      return errno;
    }

    uint8_t byte=PING_REQ_ID;

    for(;;) {

      while(write(fd, &byte, 1)!=1){}

      if(tcdrain(fd) < 0) {
	perror("tcflush serial");
	return errno;
      }

      if((ret=recv_cmd(fd, icmd))>0 && icmd->id==PING_RESP_ID) break;
    }
    //Synced

    if(tcflush(fd, TCIFLUSH) < 0) {
      perror("tcflush serial");
      return errno;
    }
  }

  return 0;
}
