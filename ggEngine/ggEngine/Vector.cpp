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
float Vector::Distance(const Vector& v){
	return sqrt((v.x - x)*(v.x - x) + (v.y - y)*(v.y - y));
}
float Vector::Distance(const Vector& vectorA, const Vector& vectorB){
	return sqrt((vectorB.x - vectorA.x)*(vectorB.x - vectorA.x) + (vectorB.y - vectorA.y)*(vectorB.y - vectorA.y));
}
float Vector::DotProduct(const Vector& v){
	return x*v.x + y*v.y;
}
float Vector::DotProduct(const Vector& vectorA, const Vector& vectorB){
	return vectorA.x*vectorB.x + vectorA.y*vectorB.y;
}
Vector Vector::CrossProduct(const Vector& v){
	 return Vector(x * v.y - y * v.x);
}
Vector3 Vector::CrossProduct(const Vector3& a, const Vector3& b){
	return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.z); //(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)
}
Vector Vector::ProjectionTo(const Vector&){
	return Vector();
}
Vector Vector::Rotate(const Vector& vector, float angle){
	float x = this->x - vector.x;
	float y = this->y - vector.y;

	float x_prime = vector.x + ((x * cos(angle)) - (y * sin(angle)));
	float y_prime = vector.y + ((x * sin(angle)) + (y * cos(angle)));

	return Vector(x_prime, y_prime);
}


