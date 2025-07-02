#include <time.h>

int get_current_hour(void) {
    time_t cur_time = time(NULL);
    struct tm *local_time = localtime(&cur_time);
    return local_time->tm_hour;
}