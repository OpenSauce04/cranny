#include "vendor/miniaudio/miniaudio.h"

#define CLEAR_LINE "\x1b[2K"
#define LEFT_PADDING "              "
#define NEWLINE "\r\n"
#define PREVIOUS_LINE "\x1b[1F"

#define VOLUME_DEFAULT 100
#define VOLUME_INCREMENT 10
#define VOLUME_MAX 200
#define VOLUME_MIN 0

extern ma_engine g_engine;
extern ma_resource_manager g_resource_manager;
extern ma_sound g_sound;
extern short g_volume;

inline float get_real_volume(void) {
    return (float)g_volume / 100;
}
