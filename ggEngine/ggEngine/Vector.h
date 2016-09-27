#pragma once
#include <d3dx9.h>
#include <cmath>
#include "Vector3.h"
class Matrix;
class Vector :public D3DXVECTOR2{
public:
	Vector(float x, float y);
	Vector(float f);
	Vector(const D3DXVECTOR2 &v);
	Vector();
	~Vector();
	Vector Normalize();
	void TransformNormal(const Matrix* mat);
	void TransformCord(const Matrix* mat);
	float Length();
	Vector Rotate(const Vector& p, float angle);
	static float Distance(const Vector& vectorA, const Vector& vectorB);
	static float DotProduct(const Vector& vectorA, const Vector& vectorB);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);

};