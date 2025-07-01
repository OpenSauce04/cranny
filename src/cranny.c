#include "miniaudio.h"

#include <stdio.h>

int main()
{
    ma_result result;
    ma_engine engine;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

    ma_sound sound;
    ma_sound_init_from_file(&engine, "/Users/daniel/Documents/sample.wav", 0, NULL, NULL, &sound);
    ma_sound_set_looping(&sound, 1);
    ma_sound_start(&sound);

    printf("Press Enter to quit...");
    getchar();

    ma_engine_uninit(&engine);

    return 0;
}
