#pragma once
#include <d3dx9math.h>
#include "Vector.h"
#include <string>
namespace ggEngine {
	class Matrix :public D3DXMATRIX {
	public:
		Matrix() {};
		virtual ~Matrix() {};
		Matrix(CONST D3DXMATRIX &mat);
		Matrix(CONST FLOAT *mat);
		Matrix(CONST D3DMATRIX &mat);
		Matrix(CONST D3DXFLOAT16 *mat);
		Matrix(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
			FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
			FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
			FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44);
		Matrix& operator *= (CONST D3DXMATRIX& value);
		Matrix& operator += (CONST D3DXMATRIX& value);
		Matrix& operator -= (CONST D3DXMATRIX& value);
		Matrix& operator *= (FLOAT value);
		Matrix& operator /= (FLOAT value);


		// binary operators
		Matrix operator * (CONST D3DXMATRIX& value) const;
		Matrix operator + (CONST D3DXMATRIX& value) const;
		Matrix operator - (CONST D3DXMATRIX& value) const;
		Matrix operator * (FLOAT value) const;
		Matrix operator / (FLOAT value) const;



		static Matrix CreateTranslateMatrix(double x, double y);
		static Matrix CreateScaleMatrix(double x, double y);
		static Matrix CreateRotateMatrix(double angle);

		std::string ToString() const;
	};
}