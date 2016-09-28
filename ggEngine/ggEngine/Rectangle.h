#pragma once
#include "Vector.h"
#include "Shape.h"
namespace ggEngine {
	class Rectangle : public Shape {
	public:
		Rectangle(float width, float height);
		~Rectangle();
		float GetArea();
		void Destroy();
		void Transform(Matrix transformMatrix);
		Vector p1, p2, p3, p4, pCenter;
		float width, height;
	};
}