#include "Rectangle.h"
#include "Matrix.h"
#include "Vector.h"
ggEngine::Rectangle::Rectangle(double width, double height)
{
	this->width = width;
	this->height = height;
	p1 = Vector(0, 0);
	p2 = Vector(0 + width, 0);
	p3 = Vector(0 + width, 0 + height);
	p4 = Vector(0, 0 + height);
	pCenter = p3 / 2;
	SetAnchor(Vector(0, 0));
}

ggEngine::Rectangle::~Rectangle()
{
}

double ggEngine::Rectangle::GetArea()
{
	return Vector::Distance(p1, p2)*Vector::Distance(p2, p3);
}

void ggEngine::Rectangle::Destroy()
{
}

void ggEngine::Rectangle::Transform(Vector position, double width, double height)
{
	this->width = width;
	this->height = height;

	Transform(position);
}

void ggEngine::Rectangle::Transform(Vector position)
{
	pCenter.x = position.x + this->width*(0.5 - this->anchor.x);
	pCenter.y = position.y + this->height*(0.5 - this->anchor.y);


	double dtX = this->width / 2.0;
	double dtY = this->height / 2.0;

	p1.y = p2.y = pCenter.y - dtY;
	p3.y = p4.y = pCenter.y + dtY;

	p1.x = p4.x = pCenter.x - dtX;
	p2.x = p3.x = pCenter.x + dtX;
}

double ggEngine::Rectangle::GetLeft()
{
	return p1.x;
}

double ggEngine::Rectangle::GetRight()
{
	return p2.x;
}

double ggEngine::Rectangle::GetUp()
{
	return p1.y;
}

double ggEngine::Rectangle::GetDown()
{
	return p3.y;
}

double ggEngine::Rectangle::GetWidth()
{
	return p2.x - p1.x;
}

double ggEngine::Rectangle::GetHeight()
{
	return p4.y - p1.y;
}

ggEngine::Vector ggEngine::Rectangle::GetPivotPoint()
{
	Vector pivot;
	pivot.x = pCenter.x - this->width*(0.5 - this->anchor.x);
	pivot.y = pCenter .y - this->height*(0.5 - this->anchor.y);
	return pivot;
}

void ggEngine::Rectangle::Translate(Vector translate)
{
	p1 += translate;
	p2 += translate;
	p3 += translate;
	p4 += translate;
	pCenter += translate;
}

