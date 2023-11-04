#include "controller.h"

struct globals gGlobals;

int main(int nargs, const char* args[])
{

  if(nargs<2) {
    fprintf(stderr,"Usage: %s device baud_rate [commands]\n",args[0]);
    return 1;
  }

  fprintf(stderr,"Opening '%s'\n",args[1]);
  sl_device sl_dev;

  sl_init(&sl_dev);
  uint32_t sbuf;
  sscanf(args[2],"%" PRIu32, &sbuf);

  args+=3;
  nargs-=3;
  gGlobals.nargs=nargs;
  gGlobals.args=args;

  //if(sl_start(&sl_dev, args[1], sbuf)<0) return -1;

  config(args, nargs);
  return 0;

  struct req_resp rr;

  if(!send_receive_ping_cmd(&sl_dev, &rr)) {
    printf("Ping succeeded!\n");
  }

  sl_close(&sl_dev);

  return 0;
}
