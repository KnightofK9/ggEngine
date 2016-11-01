#include "Rectangle.h"
#include "Matrix.h"
ggEngine::Rectangle::Rectangle(double width, double height)
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

double ggEngine::Rectangle::GetArea()
{
	return Vector::Distance(p1, p2)*Vector::Distance(p2, p3);
}

void ggEngine::Rectangle::Destroy()
{
}

void ggEngine::Rectangle::Transform(Vector position)
{
	pCenter.x = position.x - this->width*(0.5 - this->anchor.x);
	pCenter.y = position.y - this->height*(0.5 - this->anchor.y);

	double dtX = this->width / 2.0;
	double dtY = this->height / 2.0;

	p1.y = p2.y = pCenter.y - dtY;
	p3.y = p4.y = pCenter.y + dtY;

	p1.x = p4.x = pCenter.x - dtX;
	p2.x = p3.x = pCenter.x + dtX;
}

