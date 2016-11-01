#include "Circle.h"

ggEngine::Circle::Circle(double radius)
{
	this->radius = radius;
	this->pCenter = Vector(radius, radius);
}

ggEngine::Circle::~Circle()
{
}

double ggEngine::Circle::GetArea()
{
	return MATH_PI*radius*radius;
}

void ggEngine::Circle::Destroy()
{
}

void ggEngine::Circle::Transform(Vector position)
{
	
}


