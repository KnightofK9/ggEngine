#include "Circle.h"

ggEngine::Circle::Circle(float radius)
{
	this->radius = radius;
	this->pCenter = Vector(radius, radius);
}

ggEngine::Circle::~Circle()
{
}

float ggEngine::Circle::GetArea()
{
	return MATH_PI*radius*radius;
}

void ggEngine::Circle::Destroy()
{
}

void ggEngine::Circle::Transform(Matrix transformMatrix)
{
	pCenter.SetTransform(transformMatrix);
}

