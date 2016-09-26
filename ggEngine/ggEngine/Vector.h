#pragma once
#include <d3dx9.h>
#include <cmath>
#include "Vector3.h"
class Vector :public D3DXVECTOR2{
public:
	Vector(float x, float y);
	Vector(float f);
	Vector(const D3DXVECTOR2 &v);
	Vector();
	~Vector();
	Vector Normalize();
	float Length();
	float Distance(const Vector& v);
	float DotProduct(const Vector& v);
	Vector ProjectionTo(const Vector& v);
	Vector Rotate(const Vector& p, float angle);
	static float Distance(const Vector& vectorA, const Vector& vectorB);
	static float DotProduct(const Vector& vectorA, const Vector& vectorB);
	Vector CrossProduct(const Vector&v);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);

};