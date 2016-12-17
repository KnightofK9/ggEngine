#pragma once
#include <d3dx9.h>
#include <cmath>
#include "Vector3.h"
#include "Json.h"
#include <string>
namespace ggEngine {
	class Matrix;
	class Vector :public D3DXVECTOR2 {
	public:
		Vector(std::string json);
		Vector(double x, double y);
		Vector(double f);
		Vector(const Vector& v);
		Vector(Vector* v);
		Vector(const D3DXVECTOR2 &v);
		Vector();
		virtual ~Vector();
		Vector Normalize();
		void TransformNormal(Matrix mat);
		void TransformCord(Matrix mat);
		double Length();
		Vector Rotate(const Vector& p, double angle);
		static double Distance(const Vector& vectorA, const Vector& vectorB);
		static double DotProduct(const Vector& vectorA, const Vector& vectorB);
		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
		std::string ToString();
		static Vector Zero(){ return Vector(0, 0); }
	private:
	};
}