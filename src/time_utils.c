#include "time_utils.h"
#include "moon_utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void get_current_celestial_emoji(char *buf) {
    int cur_hour = get_current_hour();
    if (cur_hour >= DAY_FIRST_HOUR && cur_hour <= DAY_FINAL_HOUR) {
        strcpy(buf, "\xF0\x9F\x8C\xA4\xEF\xB8\x8F");
    } else {
        get_current_moon_emoji(buf);
    }
}

int get_current_hour(void) {
    time_t cur_time = time(NULL);
    struct tm *local_time = localtime(&cur_time);
    return local_time->tm_hour;
}

void hour_to_am_pm(char *buf, int hour) {
    if (hour == 0) {
        sprintf(buf, "12");
    } else if (hour > 12) {
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
