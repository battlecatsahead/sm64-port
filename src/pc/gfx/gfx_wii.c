#ifdef TARGET_WII

#include "macros.h" // for UNUSED

#include "gfx_wii.h"

static GXRModeObj *rmode;
static void *framebuffer[2];
static bool fb;

static void gfx_wii_init(UNUSED const char *game_name, UNUSED bool start_in_fullscreen)
{
    VIDEO_Init();
    VIDEO_SetBlack(true);

    rmode = VIDEO_GetPreferredMode(NULL);

    // double-buffering
    framebuffer[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    framebuffer[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    VIDEO_Configure(rmode);

    VIDEO_SetNextFramebuffer(framebuffer[fb]);
    VIDEO_SetBlack(false);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE)
        VIDEO_WaitVSync();
}

static void gfx_wii_set_keyboard_callbacks(UNUSED bool (*on_key_down)(int scancode), UNUSED bool (*on_key_up)(int scancode), UNUSED void (*on_all_keys_up)(void))
{
}

static void gfx_wii_set_fullscreen_changed_callback(UNUSED void (*on_fullscreen_changed)(bool is_now_fullscreen))
{
}

static void gfx_wii_set_fullscreen(UNUSED bool enable)
{
}

static void gfx_wii_main_loop(void (*run_one_game_iter)(void))
{
    run_one_game_iter();
}

static void gfx_wii_get_dimensions(uint32_t *width, uint32_t *height)
{
    *width = rmode->fbWidth;
    *height = rmode->xfbHeight;
}

static void gfx_wii_handle_events(void)
{
}

static bool gfx_wii_start_frame(void)
{
    return true;
}

static void gfx_wii_swap_buffers_begin(void)
{
    fb ^= 1; // flip frame buffer

    GX_CopyDisp(framebuffer[fb], GX_TRUE);
    GX_Flush();

    VIDEO_SetNextFramebuffer(framebuffer[fb]);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    // Interlaced screens require two frames to update
    if (rmode->viTVMode &VI_NON_INTERLACE) {
        VIDEO_WaitVSync();
    }

    // 30FPS hack
    VIDEO_WaitVSync();
}

static void gfx_wii_swap_buffers_end(void)
{
}

static double gfx_wii_get_time(void)
{
    return 0.0;
}

struct GfxWindowManagerAPI gfx_wii =
{
    gfx_wii_init,
    gfx_wii_set_keyboard_callbacks,
    gfx_wii_set_fullscreen_changed_callback,
    gfx_wii_set_fullscreen,
    gfx_wii_main_loop,
    gfx_wii_get_dimensions,
    gfx_wii_handle_events,
    gfx_wii_start_frame,
    gfx_wii_swap_buffers_begin,
    gfx_wii_swap_buffers_end,
    gfx_wii_get_time
};

#endif
