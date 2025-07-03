#include "cranny.h"
#include "path_utils.h"
#include "sound_utils.h"
#include "time_utils.h"
#include "vendor/miniaudio/miniaudio.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

ma_engine g_engine;
ma_resource_manager g_resource_manager;
ma_sound g_sound;

int main() {
    // Init miniaudio
    init_sound_engine();

    // Init misc values
    char tracks_directory_buf[MAX_PATH_LENGTH];
    get_tracks_path(tracks_directory_buf);
    int cur_hour = -1;
    int first_loop = true;

    // Main loop
    while (true) {
        int new_hour = get_current_hour();
        if (new_hour != cur_hour) {
            // Update current hour
            cur_hour = new_hour;

            // Find path for next track
            char track_path_buf[MAX_PATH_LENGTH];
            strcpy(track_path_buf, tracks_directory_buf);
            strcat(track_path_buf, "/");
            sprintf(track_path_buf + strlen(track_path_buf), "%d", cur_hour);

            // Get human time
            char human_time_buf[HUMAN_TIME_BUFFER_SIZE];
            hour_to_am_pm(human_time_buf, cur_hour);

            // Get emoji for current time
            char cur_celestial_emoji_buf[8];
            get_current_celestial_emoji(cur_celestial_emoji_buf);

            // Print message
            char time_descriptor_buf[10];
            char extra_time_padding_buf[4] = "";
            if (first_loop) {
                strcpy(time_descriptor_buf, "currently");
                first_loop = false;
            } else {
                strcpy(time_descriptor_buf, "now");
                strcpy(extra_time_padding_buf, "   ");
                printf(SEPARATOR_STRING "\n");
            }

            printf("\n"
                   "           %s\n"
                   "  %sIt is %s %s.\n"
                   "    Playing track %d.\n\n",
                   cur_celestial_emoji_buf, extra_time_padding_buf,
                   time_descriptor_buf, human_time_buf, cur_hour);

            play_sound(track_path_buf);
        }
        sleep(MAIN_LOOP_DELAY);
    }

    stop_sound_engine();
    return 0;
}
