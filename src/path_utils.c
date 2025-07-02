#include "path_utils.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *get_config_path(void) {
    static char config_path_buf[MAX_PATH_LENGTH];
    strcpy(config_path_buf, get_home_path());
    strcat(config_path_buf, "/.config/cranny");
    return config_path_buf;
}

const char *get_home_path(void) {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) {
        perror("getpwuid");
        exit(1);
    }

    return pw->pw_dir;
}

const char *get_tracks_path(void) {
    static char tracks_path_buf[MAX_PATH_LENGTH];
    strcpy(tracks_path_buf, get_config_path());
    strcat(tracks_path_buf, "/tracks");
    return tracks_path_buf;
}
