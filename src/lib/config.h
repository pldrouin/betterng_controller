#ifndef _CONTROLLER_CONFIG_
#define _CONTROLLER_CONFIG_

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "globals.h"
#include "args.h"
#include "ht.h"

int config();
void config_ht_populate();

int config_config(void);
int config_olog(void);
int config_elog(void);
int config_prompt(void);

#endif
