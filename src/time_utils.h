#define HUMAN_TIME_BUFFER_SIZE 5 // 4 characters + 1 null

int get_current_hour(void);
void hour_to_am_pm(char *buf, int hour);
