#include "Matrix.h"

Matrix::Matrix(CONST D3DXMATRIX &mat):D3DXMATRIX(mat)
{
}

Matrix::Matrix(CONST FLOAT * mat) : D3DXMATRIX(mat)
{
}

Matrix::Matrix(CONST D3DMATRIX & mat) : D3DXMATRIX(mat)
{
}

Matrix::Matrix(CONST D3DXFLOAT16 * mat):D3DXMATRIX(mat)
{
	
}

Matrix::Matrix(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14, FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24, FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34, FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44): D3DXMATRIX(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44)
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

Matrix  Matrix::CreateTranslateMatrix(float x, float y)
{
	Matrix mat;
	D3DXMatrixTranslation(&mat, x, y, 0);
	return mat;
}

Matrix  Matrix::CreateScaleMatrix(float x, float y)
{
	Matrix mat;
	D3DXMatrixScaling(&mat, x, y, 0);
	return mat;
}

Matrix  Matrix::CreateRotateMatrix(float angle)
{
	Matrix mat;
	D3DXMatrixRotationZ(&mat, angle);
	return mat;
}


