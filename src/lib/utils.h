#ifndef _UTILS_
#define _UTILS_

#include <time.h>
#include <stdio.h>
#include <ctype.h>

#define BSTR "\e[1m"
#define UBSTR "\e[m"

static inline void clock_gettime_plus_ms(struct timespec* spec, long ms)
{
    clock_gettime(CLOCK_REALTIME, spec);
    uint64_t nsec = spec->tv_nsec + ms * 1000000;
    spec->tv_nsec = nsec % 1000000000;
    spec->tv_sec += nsec / 1000000000;
}

static inline void printtime()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    printf("%li.%li\n",now.tv_sec,now.tv_nsec);
}

static inline void tolowerstr(char* str)
{
  for(; *str; ++str) *str = tolower(*str);
}

#endif
