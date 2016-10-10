#include "Matrix.h"

namespace ggEngine {
	Matrix::Matrix(CONST D3DXMATRIX &mat) :D3DXMATRIX(mat)
	{
	}

	Matrix::Matrix(CONST FLOAT * mat) : D3DXMATRIX(mat)
	{
	}

	Matrix::Matrix(CONST D3DMATRIX & mat) : D3DXMATRIX(mat)
	{
	}

	Matrix::Matrix(CONST D3DXFLOAT16 * mat) : D3DXMATRIX(mat)
	{

	}

	Matrix::Matrix(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14, FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24, FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34, FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44) : D3DXMATRIX(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44)
	{
	}

	Matrix & Matrix::operator*=(CONST D3DXMATRIX &value)
	{
		return  Matrix(D3DXMATRIX::operator*=(value));
	}

	Matrix & Matrix::operator+=(CONST D3DXMATRIX &value)
	{
		return  Matrix(D3DXMATRIX::operator+=(value));
	}

	Matrix & Matrix::operator-=(CONST D3DXMATRIX &value)
	{
		return  Matrix(D3DXMATRIX::operator-=(value));
	}

	Matrix & Matrix::operator*=(FLOAT value)
	{
		return  Matrix(D3DXMATRIX::operator*=(value));
	}

	Matrix & Matrix::operator/=(FLOAT value)
	{
		return  Matrix(D3DXMATRIX::operator/=(value));
	}


	Matrix Matrix::operator*(CONST D3DXMATRIX & value) const
	{
		return  Matrix(D3DXMATRIX::operator*(value));
	}

	Matrix Matrix::operator+(CONST D3DXMATRIX & value) const
	{
		return  Matrix(D3DXMATRIX::operator+(value));
	}

	Matrix Matrix::operator-(CONST D3DXMATRIX & value) const
	{
		return  Matrix(D3DXMATRIX::operator-(value));
	}

	Matrix Matrix::operator*(FLOAT value) const
	{
		return  Matrix(D3DXMATRIX::operator*(value));
	}

	Matrix Matrix::operator/(FLOAT value) const
	{
		return  Matrix(D3DXMATRIX::operator/(value));
	}

	Matrix  Matrix::CreateTranslateMatrix(double x, double y)
	{
		Matrix mat;
		D3DXMatrixTranslation(&mat, x, y, 0);
		return mat;
	}

	Matrix  Matrix::CreateScaleMatrix(double x, double y)
	{
		Matrix mat;
		D3DXMatrixScaling(&mat, x, y, 0);
		return mat;
	}

	Matrix  Matrix::CreateRotateMatrix(double angle)
	{
		Matrix mat;
		D3DXMatrixRotationZ(&mat, angle);
		return mat;
	}
	std::string Matrix::ToString() const
	{
		return (std::to_string(_11) + " " + std::to_string(_12) + " " + std::to_string(_13) + " " + std::to_string(_14) + "\n" +
			std::to_string(_21) + " " + std::to_string(_22) + " " + std::to_string(_23) + " " + std::to_string(_24) + "\n" +
			std::to_string(_31) + " " + std::to_string(_32) + " " + std::to_string(_33) + " " + std::to_string(_34) + "\n" +
			std::to_string(_41) + " " + std::to_string(_42) + " " + std::to_string(_43) + " " + std::to_string(_44));
	}
}

