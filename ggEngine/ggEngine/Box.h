#pragma once
#include <d3d9.h>
namespace ggEngine {
	struct Box {
		double x, y;
		double w, h;
		double vx, vy;
		RECT GetRect() { return RECT{x,y,x+w,y+h}; }
	};
}