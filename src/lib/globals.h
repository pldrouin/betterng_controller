#ifndef _CONTROLLER_GLOBALS_
#define _CONTROLLER_GLOBALS_

#include <stdio.h>
#include "ht.h"

struct globals
{
  struct ht* ht;
  int nargs;
  const char** args;
  FILE **fptra;
  int fptri;
  char pbuf[1024];
  int parc;

  int plength;

  int oldstdout;
  int oldstderr;
  int oout;
  int eout;
};

extern struct globals gGlobals;

#endif
