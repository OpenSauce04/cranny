#include "vendor/miniaudio/miniaudio.h"

#define CLEAR_LINE "\x1b[2K"
#define LEFT_PADDING "                "
#define NEWLINE "\r\n"
#define PREVIOUS_LINE "\x1b[1F"

#define VOLUME_INCREMENT 0.1
#define VOLUME_MAX 2.0
#define VOLUME_MIN 0.0

extern ma_engine g_engine;
extern ma_resource_manager g_resource_manager;
extern ma_sound g_sound;
extern float g_volume;
