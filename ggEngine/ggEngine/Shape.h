#pragma once
#include "GGObject.h"
#include "Matrix.h"
#include "ConstantEnum.h"
namespace ggEngine {
	class Shape: public GGObject {
	public:
		Shape() {
			this->anchor = Vector(0, 0);
		}
		virtual double GetArea() = 0;
		virtual void Transform(Vector position) = 0;
		void SetAnchor(Vector anchor) {
			this->anchor = anchor;
		}
	protected:
		Vector anchor;
	};
}