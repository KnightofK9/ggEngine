#pragma once
#include <d3dx9.h>
#include <cmath>
#include "Vector3.h"
#include <string>
namespace ggEngine {
	class Matrix;
	class Vector :public D3DXVECTOR2 {
	public:
		Vector(float x, float y);
		Vector(float f);
		Vector(const D3DXVECTOR2 &v);
		Vector();
		~Vector();
		Vector Normalize();
		void TransformNormal(Matrix mat);
		void TransformCord(Matrix mat);
		float Length();
		Vector Rotate(const Vector& p, float angle);
		void SetTransform(Matrix mat);
		static float Distance(const Vector& vectorA, const Vector& vectorB);
		static float DotProduct(const Vector& vectorA, const Vector& vectorB);
		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
		std::string ToString();
	private:
		float orgX, orgY;
	};
}