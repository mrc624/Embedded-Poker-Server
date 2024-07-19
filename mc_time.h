#ifdef __cplusplus
extern "C" {
#endif

#define SECONDS_IN_DAY SECONDS_IN_HOUR * 24
#define SECONDS_IN_HOUR SECONDS_IN_MIN * 60
#define SECONDS_IN_MIN 60

void time_init();

const char * time_length_format(time_t time);
const char* get_local_time_string(void);
const char* get_utc_string(void);
const char* get_uptime_string(void);
time_t get_utc(void);
time_t get_uptime(void);

#ifdef __cplusplus
}
#endif