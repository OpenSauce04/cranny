// Adapted from https://gist.github.com/lpar/821408a9dea14736c12d3ba81b942e29

#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * Disclaimer:
 *
 * Moon phase calculation function found online and may be
 * inaccurate. Not intended for astrogation, or for treatment
 * or management of lycanthropy.
 *
 * See http://www.voidware.com/moon_phase.htm
 *
 * Additional code by meta@pobox.com
 */

int moon_phase(int y, int m, int d) {
    int c, e;
    double jd;
    int b;

    if (m < 3) {
        y--;
        m += 12;
    }
    ++m;
    c = 365.25 * y;
    e = 30.6 * m;
    jd = c + e + d - 694039.09; /* jd is total days elapsed */
    jd /= 29.53;                /* divide by the moon cycle (29.53 days) */
    b = jd;                     /* int(jd) -> b, take integer part of jd */
    jd -= b; /* subtract integer part to leave fractional part of original jd */
    b = jd * 8 + 0.5; /* scale fraction from 0-8 and round by adding 0.5 */
    b = b & 7;        /* 0 and 8 are the same so turn 8 into 0 */
    return b;
}

char *moon_emoji(int p) {
    switch (p) {
    case 0:
        return "\xf0\x9f\x8c\x91";
    case 1:
        return "\xf0\x9f\x8c\x92";
    case 2:
        return "\xf0\x9f\x8c\x93";
    case 3:
        return "\xf0\x9f\x8c\x95";
    case 4:
        return "\xf0\x9f\x8c\x96";
    case 5:
        return "\xf0\x9f\x8c\x94";
    case 6:
        return "\xf0\x9f\x8c\x97";
    case 7:
        return "\xf0\x9f\x8c\x98";
    default:
        return "";
    }
}

void get_current_moon_emoji(char *buf) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int p = moon_phase(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    strcpy(buf, moon_emoji(p));
}
