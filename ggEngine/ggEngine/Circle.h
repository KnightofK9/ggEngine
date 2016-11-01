#pragma once
#include "Shape.h"
#include "NiseVector.h"
namespace ggEngine {
	class Circle: public Shape {
	public:
		Circle(double radius);
		~Circle();
		double GetArea();
		void Destroy();
		void Transform(Vector position);
		NiseVector pCenter;
		double radius;
	private:
	};
}