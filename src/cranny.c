#include "cranny.h"
#include "input_utils.h"
#include "keycodes.h"
#include "math_utils.h"
#include "path_utils.h"
#include "sound_utils.h"
#include "time_utils.h"
#include "vendor/miniaudio/miniaudio.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ma_engine g_engine;
ma_resource_manager g_resource_manager;
ma_sound g_sound;
float g_volume = 1.0;

static inline void print_volume() {
    printf(CLEAR_LINE PREVIOUS_LINE CLEAR_LINE "      Volume: %d%%" NEWLINE,
           (int)round(g_volume * 100));
    fflush(stdout);
}

int main() {
    // Init miniaudio
    init_sound_engine();

    // Set up terminal for raw input
    setup_termio();

    // Init misc values
    char tracks_directory_buf[MAX_PATH_LENGTH];
    get_tracks_path(tracks_directory_buf);
    int cur_hour = -1;
    int first_loop = true;

    // Show controls
    printf("  , Volume down  |  . Volume up  |  Ctrl+C Exit" NEWLINE
               SEPARATOR_STRING SEPARATOR_STRING NEWLINE);

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
                printf(
                    PREVIOUS_LINE CLEAR_LINE NEWLINE SEPARATOR_STRING NEWLINE);
            }

            printf(NEWLINE "           %s" NEWLINE "  %sIt is %s %s." NEWLINE
                           "    Playing track %d." NEWLINE NEWLINE,
                   cur_celestial_emoji_buf, extra_time_padding_buf,
                   time_descriptor_buf, human_time_buf, cur_hour);
            print_volume();

            play_sound(track_path_buf);
        }

        char input;
        read(STDIN_FILENO, &input, 1);

        switch (input) {
        case COMMA_KEYCODE: // Volume down
            g_volume -= VOLUME_INCREMENT;
            break;
        case PERIOD_KEYCODE: // Volume up
            g_volume += VOLUME_INCREMENT;
            break;
        }

        if (input == COMMA_KEYCODE || input == PERIOD_KEYCODE) {
            g_volume = clamp(g_volume, 0.0, 2.0);
            ma_sound_set_volume(&g_sound, g_volume);
            print_volume();
        }
    }

    stop_sound_engine();
    return 0;
}
