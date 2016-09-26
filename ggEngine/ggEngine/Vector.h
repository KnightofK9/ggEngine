#pragma once
#include <d3dx9.h>
#include <cmath>
class Vector :public D3DXVECTOR2{
public:
	Vector(float x, float y);
	Vector(float f);
	Vector(const D3DXVECTOR2 &v);
	Vector();
	~Vector();
	Vector Normalize();
	float Length();
	friend float Distance(const Vector& vectorA, const Vector& vectorB);
	Vector DotProduct(const Vector&);
	Vector CrossProduct(const Vector&);
	Vector ProjectionTo(const Vector&);
};