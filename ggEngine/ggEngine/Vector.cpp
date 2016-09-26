#include "Vector.h"
Vector::Vector(float x, float y) : D3DXVECTOR2(x,y){

}
Vector::Vector(float f) : D3DXVECTOR2(f, f){

}
Vector::Vector(const D3DXVECTOR2 & v) : D3DXVECTOR2(v.x, v.y)
{
}
Vector::Vector() : D3DXVECTOR2(0, 0){

}
Vector::~Vector() {

}
Vector Vector::Normalize(){
	float length = this->Length();
	return Vector(x / length, y / length);
}
float Vector::Length(){
	return sqrt(x*x + y*y);
}
float Distance(const Vector& vectorA,const Vector& vectorB){
	return sqrt((vectorB.x - vectorA.x)*(vectorB.x - vectorA.x) + (vectorB.y - vectorA.y)*(vectorB.y - vectorA.y));
}
Vector Vector::DotProduct(const Vector&){

}
Vector Vector::CrossProduct(const Vector&){

}
Vector Vector::ProjectionTo(const Vector&){

}


