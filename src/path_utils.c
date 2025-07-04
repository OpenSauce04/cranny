#include "path_utils.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_data_path(char *buf) {
    get_home_path(buf);
    strcat(buf, "/.local/share/cranny");
}

void get_home_path(char *buf) {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) {
        perror("getpwuid");
        exit(1);
    }

    strcpy(buf, pw->pw_dir);
}

void get_tracks_path(char *buf) {
    get_data_path(buf);
    strcat(buf, "/tracks");
}
