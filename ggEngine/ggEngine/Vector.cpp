#include "Vector.h"
Vector::Vector(float x, float y) : D3DXVECTOR2(x,y){

}
Vector::Vector(const D3DXVECTOR2 & v) : D3DXVECTOR2(v.x, v.y)
{
}
Vector::Vector() : D3DXVECTOR2(0, 0){

}
Vector::~Vector() {

}
//Vector::operator FLOAT*()
//{
//}
//Vector::operator CONST FLOAT*() const
//{
//}
//Vector & Vector::operator+=(CONST D3DXVECTOR2 &)
//{
//	// TODO: insert return statement here
//}
//
//Vector Vector::operator+(CONST D3DXVECTOR2 &) const
//{
//	return Vector();
//}
//
//Vector Vector::operator-(CONST D3DXVECTOR2 &) const
//{
//	return Vector();
//}
//
//Vector Vector::operator*(FLOAT) const
//{
//	return Vector();
//}
//
//Vector Vector::operator/(FLOAT) const
//{
//	return Vector();
//}
//
//BOOL Vector::operator==(CONST D3DXVECTOR2 &) const
//{
//	return 0;
//}
//
//BOOL Vector::operator!=(CONST D3DXVECTOR2 &) const
//{
//	return 0;
//}
