#ifndef _CONTROLLER_GLOBALS_
#define _CONTROLLER_GLOBALS_

#include <stdio.h>
#include "args.h"
#include "ht.h"

#include "serial_link.h"

#define PBUF_SIZE (1024)

struct globals
{
  struct ht* ht;
  args_info a_h;
  char pbuf[PBUF_SIZE];

  int plength;

  int oldstdout;
  int oldstderr;
  int oout;
  int eout;

  bool interactive;

  sl_device sl_dev;
};

extern struct globals gGlobals;

#endif
