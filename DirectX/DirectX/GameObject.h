#pragma once
#include "Point.h"
class GameObject {
public:
	GameObject(float x, float y);
	void destroy();
	Point point;
};