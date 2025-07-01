#include <stdio.h>
#include "abstractions.h"
#include "miniaudio.h"

ma_engine engine;
ma_sound sound;

int main()
{
    init_sound_engine();

    play_sound("/Users/daniel/Documents/ninjatuna.wav");

    printf("Press Enter to start new sound...");
    getchar();

    play_sound("/Users/daniel/Documents/ninjatuna.wav");

    printf("Press Enter to stop sound...");
    getchar();

    stop_sound();

    printf("Press Enter to start sound again...");
    getchar();

    play_sound("/Users/daniel/Documents/ninjatuna.wav");

    printf("Press Enter to quit...");
    getchar();

    stop_sound_engine();

    return 0;
}
