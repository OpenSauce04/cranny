#include "cranny.h"
#include "miniaudio.h"
#include "path_utils.h"
#include "sound_utils.h"
#include "time_utils.h"
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
    char tracks_directory_buf[MAX_PATH_LENGTH];
    get_tracks_path(tracks_directory_buf);
    int cur_hour = -1;

    // Main loop
    while (true) {
        int new_hour = get_current_hour();
        if (cur_hour != new_hour) {
            // Update current hour
            cur_hour = new_hour;

            // Find path for next track
            char track_path_buf[MAX_PATH_LENGTH];
            strcpy(track_path_buf, tracks_directory_buf);
            strcat(track_path_buf, "/");
            sprintf(track_path_buf + strlen(track_path_buf), "%d", cur_hour);

            // Print message
            char human_time_buf[HUMAN_TIME_BUFFER_SIZE];
            hour_to_am_pm(human_time_buf, cur_hour);
            printf(SEPARATOR_STRING "\nIt is currently %s.\nPlaying track %d.\n.", human_time_buf, cur_hour);

            play_sound(track_path_buf);
        }
        sleep(MAIN_LOOP_DELAY);
    }

    stop_sound_engine();
    return 0;
}
