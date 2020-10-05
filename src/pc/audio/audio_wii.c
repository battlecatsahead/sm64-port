#ifdef TARGET_WII

#include <malloc.h>
#include <string.h>

#include <asndlib.h>
#include <ogc/cache.h>

#include "macros.h"
#include "audio_api.h"

// Not great, not terrible. TODO: use aesndlib

#define BUFFER_COUNT 3
#define BUFFER_SIZE 544 * 2 * 2 * sizeof(int16_t)

static int16_t *audio_buffer[BUFFER_COUNT];
static uint8_t current = 0;

static void voice_callback(int32_t voice)
{
    ASND_AddVoice(voice, audio_buffer[(current + 2) % BUFFER_COUNT], BUFFER_SIZE);
}

static bool audio_wii_init(void)
{
    for (int i = 0; i < BUFFER_COUNT; i++)
    {
        audio_buffer[i] = (int16_t *) memalign(32, BUFFER_SIZE);
        memset(audio_buffer[i], 0, BUFFER_SIZE);
        DCFlushRange(audio_buffer[i], BUFFER_SIZE);
    }

    ASND_Init();
    ASND_SetVoice(0, VOICE_STEREO_16BIT, 32000, 0, audio_buffer[current], BUFFER_SIZE, MAX_VOLUME, MAX_VOLUME, voice_callback);
    ASND_Pause(0);

    return true;
}

static int audio_wii_buffered(void)
{
    // FIXME
    return 0;
}

static int audio_wii_get_desired_buffered(void)
{
    return 1100;
}

static void audio_wii_play(const uint8_t *buf, size_t len)
{
    if (len > BUFFER_SIZE)
        return;

    memcpy(audio_buffer[current], buf, len);
    DCFlushRange(audio_buffer[current], len);
    current = (current + 1) % BUFFER_COUNT;
}

struct AudioAPI audio_wii =
{
    audio_wii_init,
    audio_wii_buffered,
    audio_wii_get_desired_buffered,
    audio_wii_play
};

#endif
