#pragma once
#include "Shape.h"
namespace ggEngine {
	class Circle: public Shape {
	public:
		Circle(double radius);
		~Circle();
		double GetArea();
		void Destroy();
		void Transform(Matrix transformMatrix);
		Vector pCenter;
		double radius;
	};
}