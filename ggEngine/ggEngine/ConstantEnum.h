#pragma once
#include <d3d9.h>
#include "Vector.h"
#define WINDOW_WIDTH ((int)800)
#define WINDOW_HEIGHT ((int)600)
#define MILISECOND_PER_UPDATE ((int)14)
#define VECTOR_ZERO (Vector(0,0))
#define DEFAULT_IMAGE ""
const int ERROR_CODE_UNKNOWN = 400;
const int ERROR_CODE_D3DERR_INVALIDCALL = 401;
const int ERROR_CODE_D3DERR_NOTAVAILABLE = 402;
const int ERROR_CODE_D3DERR_OUTOFVIDEOMEMORY = 403;
const int ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW = 404;
const int ERROR_CODE_FAIL_INIT_SPRITE_HANDLER = 405;
typedef LPCTSTR GGTEXT;
enum GameMode { GameMode_FullScreen, GameMode_Windowed };