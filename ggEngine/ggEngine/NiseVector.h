#pragma once
#include "Vector.h"
namespace ggEngine {
	class NiseVector: public Vector {
	public:
		NiseVector(double x, double y);
		NiseVector(double f);
		NiseVector(const D3DXVECTOR2 &v);
		NiseVector();
		~NiseVector();
		void SetTransform(Matrix mat);
	private:
		double orgX, orgY;
	};
}