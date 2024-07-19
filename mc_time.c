#include <stdio.h>
#include <time.h>
#include <string.h>
#include "mc_time.h"

time_t boot_time = 0;

void time_init()
{
  boot_time = time(NULL);
  printf("Boot Time: %llu\n", (long long unsigned int)(boot_time));
  printf("mc_time Initialized\n");
}

const char * time_length_format(time_t time)
{
  __uint8_t sec = time % 60;
  __uint8_t min = (time / 60) % 60;
  __uint8_t hour = (time / 60 / 60) % 24;
  __uint8_t day = (time / 60 / 60 / 24);
  static char buf[25];
  sprintf(buf, "%u.%u:%u:%u", day, hour, min, sec);
  return buf;
}

const char * get_local_time_string(void)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  return asctime(&tm);
}

const char* get_utc_string(void)
{
  time_t t = time(NULL);
  struct tm tm = *gmtime(&t);
  return asctime(&tm);
}

const char* get_uptime_string(void)
{
  return time_length_format(get_uptime());
}

time_t get_utc(void)
{
  return time(NULL);
}

time_t get_uptime(void)
{
  return get_utc() - boot_time;
}