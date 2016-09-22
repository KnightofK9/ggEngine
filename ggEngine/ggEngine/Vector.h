#pragma once
#include <d3dx9.h>
class Vector :public D3DXVECTOR2{
public:
	Vector(float x, float y);
	Vector();
	~Vector();
};