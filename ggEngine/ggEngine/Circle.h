#pragma once
#include "Shape.h"
namespace ggEngine {
	class Circle: public Shape {
	public:
		Circle(float radius);
		~Circle();
		float GetArea();
		void Destroy();
		void Transform(Matrix transformMatrix);
		Vector pCenter;
		float radius;
	};
}