#include <stdio.h>
#include <string.h>
#include <time.h>

int get_current_hour(void) {
    time_t cur_time = time(NULL);
    struct tm *local_time = localtime(&cur_time);
    return local_time->tm_hour;
}

void hour_to_am_pm(char *buf, int hour) {
    if (hour > 12) {
        sprintf(buf, "%d", hour - 12);
    } else {
        sprintf(buf, "%d", hour);
    }

    if (hour > 11) {
        strcat(buf, "pm");
    } else {
        strcat(buf, "am");
    }
}
