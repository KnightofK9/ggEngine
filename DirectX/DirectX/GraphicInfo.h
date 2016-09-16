#pragma once
#include <d3d9.h>
struct GraphicInfo {
	RECT sourcRect;
	IDirect3DSurface9 *surface;
};