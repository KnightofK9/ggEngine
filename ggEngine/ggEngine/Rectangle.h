#pragma once
#include "NiseVector.h"
#include "Shape.h"
namespace ggEngine {
	class Rectangle : public Shape {
	public:
		Rectangle(double width, double height);
		~Rectangle();
		double GetArea();
		void Destroy();
		void Transform(Vector position);
		Vector p1, p2, p3, p4, pCenter;
		double width, height;
	private:
	};
}