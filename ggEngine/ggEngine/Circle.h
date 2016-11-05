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
		void Transform(Vector position, double width, double height);
		void Transform(Vector position);
		NiseVector pCenter;
		double radius;
	private:

		// Inherited via Shape
		virtual double GetLeft() override;
		virtual double GetRight() override;
		virtual double GetUp() override;
		virtual double GetDown() override;

		// Inherited via Shape
		virtual double GetWidth() override;
		virtual double GetHeight() override;

		// Inherited via Shape
		virtual Vector GetPivotPoint() override;

		// Inherited via Shape
		virtual void Translate(Vector translate) override;
	};
}