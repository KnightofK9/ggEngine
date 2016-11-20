#pragma once
#include <d3d9.h>
#include "Vector.h"
#define GAME_WIDTH ((int)1000) //((int)1366) //(int)650 //((int)800)
#define GAME_HEIGHT ((int)1000) //((int)600)
#define WINDOW_WIDTH ((int)800)
#define WINDOW_HEIGHT ((int)800)
#define MILISECOND_PER_UPDATE ((int)2)
#define DEFAULT_MS_PER_FRAME_FOR_ANIMATION 14
#define VECTOR_ZERO (Vector(0,0))
#define DEFAULT_IMAGE ""
#define D3DFVF_TL (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define GRAVITY (double(9.81))
#define MATH_PI (double(3.1415926535897))
#define DEFAULT_COLOR D3DCOLOR_RGBA(170, 255, 0, 255)
#define PIXEL_PER_CENTIMETER 100
#define RAPIDJSON_PARSE_ERROR_NORETURN(parseErrorCode,offset) \
   throw ParseException(parseErrorCode, #parseErrorCode, offset)
#include <stdexcept>               // std::runtime_error
#include <error/error.h> // rapidjson::ParseResult
struct ParseException : std::runtime_error, rapidjson::ParseResult {
	ParseException(rapidjson::ParseErrorCode code, const char* msg, size_t offset)
		: std::runtime_error(msg), ParseResult(code, offset) {}
};
#include <reader.h>
const bool PRINT_DETAIL = false;
const int ERROR_CODE_UNKNOWN = 400;
const int ERROR_CODE_D3DERR_INVALIDCALL = 401;
const int ERROR_CODE_D3DERR_NOTAVAILABLE = 402;
const int ERROR_CODE_D3DERR_OUTOFVIDEOMEMORY = 403;
const int ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW = 404;
const int ERROR_CODE_FAIL_INIT_SPRITE_HANDLER = 405;
typedef LPCTSTR GGTEXT;
enum GameMode { GameMode_FullScreen, GameMode_Windowed };
enum PhysicsMode { PhysicsMode_AABB, PhysicsMode_AABBSwept, PhysicsMode_None };
enum SoundMode {SoundMode_Enable, SoundMode_Disable};
enum SoundType { SoundType_Sound, SoundType_Music };
enum TileType {TileType_SingleTile = 0, TileType_AnimationType};