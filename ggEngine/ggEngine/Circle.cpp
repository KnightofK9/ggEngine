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



void ggEngine::Circle::Transform(Vector position, double width, double height)
{
	
}

void ggEngine::Circle::Transform(Vector position)
{
}



double ggEngine::Circle::GetLeft()
{
	return 0.0;
}

double ggEngine::Circle::GetRight()
{
	return 0.0;
}

double ggEngine::Circle::GetUp()
{
	return 0.0;
}

double ggEngine::Circle::GetDown()
{
	return 0.0;
}

double ggEngine::Circle::GetWidth()
{
	return 0.0;
}

double ggEngine::Circle::GetHeight()
{
	return 0.0;
}

ggEngine::Vector ggEngine::Circle::GetPivotPoint()
{
	return Vector();
}

void ggEngine::Circle::Translate(Vector translate)
{
}


