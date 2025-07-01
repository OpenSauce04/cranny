#include <stdlib.h>
#include "abstractions.h"
#include "cranny.h"
#include "miniaudio.h"

void init_sound_engine() {
    ma_result result;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        exit(-1);
    }
}

void play_sound(char *path) {
    restart_sound_engine();

    ma_sound_init_from_file(&engine, path, 0, NULL, NULL, &sound);
    ma_sound_set_looping(&sound, 1);
    ma_sound_start(&sound);
}

void restart_sound_engine() {
    ma_engine_uninit(&engine);
    init_sound_engine();
}

void stop_sound() {
    ma_sound_stop(&sound);
}

void stop_sound_engine() {
    ma_engine_uninit(&engine);
}
