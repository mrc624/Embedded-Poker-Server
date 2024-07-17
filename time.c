#include <stdio.h>
#include "time.h"

long unsigned int boot_time = 0;

void init_time()
{
    boot_time = time();
}

const char *const get_local_time_string()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char buf[40];
  sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  return buf;
}

time_t get_utc()
{
  return time();
}