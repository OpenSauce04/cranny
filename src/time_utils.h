#define DAY_FIRST_HOUR 6
#define DAY_FINAL_HOUR 19
#define HUMAN_TIME_BUFFER_SIZE 5 // 4 characters + 1 null

void get_current_celestial_emoji(char *buf);
int get_current_hour(void);
void hour_to_am_pm(char *buf, int hour);
