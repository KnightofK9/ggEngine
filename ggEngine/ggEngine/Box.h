#pragma once
#include <d3d9.h>
namespace ggEngine {
	struct Box {
		double x, y;
		double w, h;
		double vx, vy;
		RECT GetRect() { return RECT{ (long)x,(long)y,(long)(x + w),(long)(y + h) }; }
	};
}