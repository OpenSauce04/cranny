#include "abstractions.h"
#include "cranny.h"
#include "miniaudio.h"
#include <stdlib.h>
#include <time.h>

int get_current_hour(void) {
    time_t cur_time = time(NULL);
    struct tm *local_time = localtime(&cur_time);
    return local_time->tm_hour;
}

void init_sound_engine(void) {
    ma_result result;

    result = ma_engine_init(NULL, &g_engine);
    if (result != MA_SUCCESS) {
        exit(-1);
    }
}

void play_sound(char *path) {
    restart_sound_engine();

    ma_sound_init_from_file(&g_engine, path, 0, NULL, NULL, &g_sound);
    ma_sound_set_looping(&g_sound, 1);
    ma_sound_start(&g_sound);
}

void restart_sound_engine(void) {
    ma_engine_uninit(&g_engine);
    init_sound_engine();
}

void stop_sound(void) { ma_sound_stop(&g_sound); }

void stop_sound_engine(void) { ma_engine_uninit(&g_engine); }
