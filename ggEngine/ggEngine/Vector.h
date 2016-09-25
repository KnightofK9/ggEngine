#pragma once
#include <d3dx9.h>
class Vector :public D3DXVECTOR2{
public:
	Vector(float x, float y);
	Vector(const D3DXVECTOR2 &v);
	Vector();
	~Vector();
	//operator FLOAT* ();
	//operator CONST FLOAT* () const;

	//// assignment operators
	//Vector& operator += (CONST D3DXVECTOR2&);
	//Vector& operator -= (CONST D3DXVECTOR2&);
	//Vector& operator *= (FLOAT);
	//Vector& operator /= (FLOAT);

	//// unary operators
	//Vector operator + () const;
	//Vector operator - () const;

	//// binary operators
	//Vector operator + (CONST D3DXVECTOR2&) const;
	//Vector operator - (CONST D3DXVECTOR2&) const;
	//Vector operator * (FLOAT) const;
	//Vector operator / (FLOAT) const;


	//BOOL operator == (CONST D3DXVECTOR2&) const;
	//BOOL operator != (CONST D3DXVECTOR2&) const;
};