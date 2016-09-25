#pragma once
#include "Shape.h"
class RectangleShape :public Shape {
public:
	RectangleShape(int width, int height);
	RectangleShape();
	~RectangleShape();
	float GetArea();
	int width;
	int height;
};