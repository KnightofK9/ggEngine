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
		void Transform(Vector position, double width, double height);
		void Transform(Vector position);
		Vector p1, p2, p3, p4, pCenter;
		double width, height;
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
	private:

		


	};
}