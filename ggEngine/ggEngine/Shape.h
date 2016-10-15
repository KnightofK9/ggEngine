#pragma once
#include "GGObject.h"
#include "Matrix.h"
#include "ConstantEnum.h"
namespace ggEngine {
	class Shape: public GGObject {
	public:
		virtual double GetArea() = 0;
		virtual void Transform(Matrix transformMatrix) = 0;
		virtual bool IsReady() = 0;
	};
}