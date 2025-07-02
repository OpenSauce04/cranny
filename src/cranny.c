#include "abstractions.h"
#include "miniaudio.h"
#include "path_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

const ma_engine g_engine;
const ma_sound g_sound;

int main() {
    // Init miniaudio
    init_sound_engine();

    // Init misc values
    const char *const tracks_path = get_tracks_path();
    int cur_hour = -1;

    // Main loop
    while (true) {
        int new_cur_hour = get_current_hour();
        if (cur_hour != new_cur_hour) {
            char sound_path_buf[MAX_PATH_LENGTH];
            strcpy(sound_path_buf, tracks_path);
            strcat(sound_path_buf, "/");
            sprintf(sound_path_buf + strlen(sound_path_buf), "%d",
                    new_cur_hour);
            printf("Playing %s\n", sound_path_buf);
            play_sound(sound_path_buf);
        }
        cur_hour = new_cur_hour;
        sleep(MAIN_LOOP_DELAY);
    }

    stop_sound_engine();
    return 0;
}
