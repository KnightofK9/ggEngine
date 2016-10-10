#pragma once
#include <d3d9.h>
namespace ggEngine {
	struct Box {
		float x, y;
		float w, h;
		float vx, vy;
		RECT GetRect() { return RECT{x,y,x+w,y+h}; }
	};
}