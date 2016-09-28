#include "Rectangle.h"
#include "Matrix.h"
ggEngine::Rectangle::Rectangle(float width, float height)
{
	this->width = width;
	this->height = height;
	p1 = Vector(0, 0);
	p2 = Vector(0 + width, 0);
	p3 = Vector(0 + width, 0 + height);
	p4 = Vector(0, 0 + height);
	pCenter = p3 / 2;
}

ggEngine::Rectangle::~Rectangle()
{
}

float ggEngine::Rectangle::GetArea()
{
	return Vector::Distance(p1, p2)*Vector::Distance(p2, p3);
}

void ggEngine::Rectangle::Destroy()
{
}

void ggEngine::Rectangle::Transform(Matrix transformMatrix)
{
	//transformMatri
	p1.SetTransform(transformMatrix);
	p2.SetTransform(transformMatrix);
	p3.SetTransform(transformMatrix);
	p4.SetTransform(transformMatrix);
	pCenter = p3 / 2;
}

