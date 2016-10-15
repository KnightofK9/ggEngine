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
		void Transform(Matrix transformMatrix);
		NiseVector pCenter;
		double radius;
		bool IsReady(){ return this->isReady; }
	private:
		bool isReady;
	};
}