#include "sound_utils.h"
#include "cranny.h"
#include "vendor/miniaudio/miniaudio.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_sound_engine(void) { // TODO: Cleanup
    ma_decoding_backend_vtable *pCustomBackendVTables[] = {
        ma_decoding_backend_libvorbis};

    ma_resource_manager_config resourceManagerConfig;
    ma_engine_config engineConfig;
    ma_result result;

    resourceManagerConfig = ma_resource_manager_config_init();
    resourceManagerConfig.ppCustomDecodingBackendVTables =
        pCustomBackendVTables;
    resourceManagerConfig.customDecodingBackendCount = 1;
    resourceManagerConfig.pCustomDecodingBackendUserData =
        NULL; /* <-- This will be passed in to the pUserData parameter of each
                 function in the decoding backend vtables. */

    result =
        ma_resource_manager_init(&resourceManagerConfig, &g_resource_manager);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize resource manager.\n");
        exit(1);
    }

    engineConfig = ma_engine_config_init();
    engineConfig.pResourceManager = &g_resource_manager;

    result = ma_engine_init(&engineConfig, &g_engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize sound engine.\n");
        exit(1);
    }
}

void play_sound(char *path) {
    restart_sound_engine();

    ma_result result;
    result = ma_sound_init_from_file(&g_engine, path, 0, NULL, NULL, &g_sound);
    if (result != MA_SUCCESS) {
        printf("Failed to load sound: %s", path);
        fflush(stdout);
    }
    ma_sound_set_volume(&g_sound, g_volume);
    ma_sound_set_looping(&g_sound, true);
    ma_sound_start(&g_sound);
}

void restart_sound_engine(void) {
    ma_engine_uninit(&g_engine);
    init_sound_engine();
}

void stop_sound(void) { ma_sound_stop(&g_sound); }

void stop_sound_engine(void) { ma_engine_uninit(&g_engine); }
