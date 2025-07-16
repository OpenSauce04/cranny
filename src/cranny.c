#include "cranny.h"
#include "input_utils.h"
#include "keycodes.h"
#include "math_utils.h"
#include "path_utils.h"
#include "sound_utils.h"
#include "time_utils.h"
#include "vendor/miniaudio/miniaudio.h"
#include "version.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vorbis/codec.h>

ma_engine g_engine;
ma_resource_manager g_resource_manager;
ma_sound g_sound;
float g_volume = 1.0;

static inline void print_volume() {
    // clang-format off
    printf(CLEAR_LINE PREVIOUS_LINE
           CLEAR_LINE PREVIOUS_LINE
           NEWLINE
           CLEAR_LINE LEFT_PADDING "    Volume: %d%%" NEWLINE,
           (int)round(g_volume * 100));
    // clang-format on
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    // Check for command line options
    { // scope
        int option_index = 0;
        struct option long_options[] = {
            {"version", no_argument, 0, 'v'},
        };

        while (optind < argc) {
            int arg = getopt_long(argc, argv, "v", long_options, &option_index);
            if (arg != -1) {
                switch (arg) {
                case 'v':
                    printf("cranny " CRANNY_VERSION_STRING
                           "\n------------------\n"
                           "miniaudio %s\n"
                           "%s\n",
                           ma_version_string(), vorbis_version_string());
                    return 0;
                }
            }
        }
    }

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
    // clang-format off
    printf(NEWLINE
           "  , Volume down  |  . Volume up  |  Ctrl+C Exit" NEWLINE
           "-------------------------------------------------" NEWLINE);
    // clang-format on

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

            // clang-format off
            // Print message
            if (first_loop) {
                first_loop = false;
            } else {
                printf(CLEAR_LINE
                       PREVIOUS_LINE CLEAR_LINE
                       PREVIOUS_LINE CLEAR_LINE
                       PREVIOUS_LINE CLEAR_LINE
                       PREVIOUS_LINE CLEAR_LINE
                       PREVIOUS_LINE CLEAR_LINE
                       PREVIOUS_LINE CLEAR_LINE);
            }

            printf(NEWLINE
                   LEFT_PADDING "         %s" NEWLINE
                   LEFT_PADDING "It is currently %s." NEWLINE
                   LEFT_PADDING "  Playing track %d." NEWLINE
                   NEWLINE
                   NEWLINE,
                   cur_celestial_emoji_buf, human_time_buf,
                   cur_hour);
            // clang-format on
            print_volume();

            play_sound(track_path_buf);
        }

        char input;
        if (read(STDIN_FILENO, &input, 1) == -1) {
            continue;
        }

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
