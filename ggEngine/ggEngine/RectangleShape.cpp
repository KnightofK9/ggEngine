#include "RectangleShape.h"

RectangleShape::RectangleShape(int width, int height)
{
	this->width = width;
	this->height = height;
}

RectangleShape::RectangleShape()
{
	this->width = 0;
	this->height - 0;
}

RectangleShape::~RectangleShape()
{
}

float RectangleShape::GetArea()
{
	return width*height;
}
