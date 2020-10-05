#ifndef GFX_WII_H
#define GFX_WII_H

#define Mtx __Mtx
#define Vtx __Vtx
#define guPerspectiveF GXguPerspectiveF
#define guPerspective GXguPerspective
#define guOrtho GXguOrtho
#define guOrthoF GXguOrthoF
#include <gccore.h>
#undef Mtx
#undef Vtx
#undef guPerspectiveF
#undef guPerspective
#undef guOrtho
#undef guOrthoF

#include "gfx_window_manager_api.h"

extern struct GfxWindowManagerAPI gfx_wii;

#endif
