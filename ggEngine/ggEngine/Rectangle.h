#pragma once
#include "Vector.h"
#include "Shape.h"
namespace ggEngine {
	class Rectangle : public Shape {
	public:
		Rectangle(double width, double height);
		~Rectangle();
		double GetArea();
		void Destroy();
		bool isReady;
		void Transform(Matrix transformMatrix);
		Vector p1, p2, p3, p4, pCenter;
		double width, height;
	};
}