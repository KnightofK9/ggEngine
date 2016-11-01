#include "Vector.h"
#include "Matrix.h"
#include "Debug.h"
namespace ggEngine {
	Vector::Vector(double x, double y) : D3DXVECTOR2(x, y) {
		this->x = x;
		this->y = y;
	}
	Vector::Vector(double f) : D3DXVECTOR2(f, f) {

	}
	Vector::Vector(const Vector & v)
	{
		this->x = v.x;
		this->y = v.y;
	}
	Vector::Vector(Vector * v)
	{
		this->x = v->x;
		this->y = v->y;
	}
	Vector::Vector(const D3DXVECTOR2 & v) : D3DXVECTOR2(v.x, v.y)
	{
	}
	Vector::Vector() : D3DXVECTOR2(0, 0) {

	}
	Vector::~Vector() {

	}
	Vector Vector::Normalize() {
		double length = this->Length();
		return Vector(x / length, y / length);
	}
	void Vector::TransformNormal(Matrix  mat)
	{
		D3DXVec2TransformNormal(this, this, &mat);
	}
	void Vector::TransformCord(Matrix  mat)
	{
		D3DXVec2TransformCoord(this, this, &mat);
	}
	double Vector::Length() {
		return sqrt(x*x + y*y);
	}
	double Vector::Distance(const Vector& vectorA, const Vector& vectorB) {
		return sqrt((vectorB.x - vectorA.x)*(vectorB.x - vectorA.x) + (vectorB.y - vectorA.y)*(vectorB.y - vectorA.y));
	}
	double Vector::DotProduct(const Vector& vectorA, const Vector& vectorB) {
		return vectorA.x*vectorB.x + vectorA.y*vectorB.y;
	}
	Vector3 Vector::CrossProduct(const Vector3& a, const Vector3& b) {
		return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.z); //(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)
	}
	std::string Vector::ToString()
	{
		return std::to_string(this->x) + "-" + std::to_string(this->y);
	}
	Vector Vector::Rotate(const Vector& vector, double angle) {
		double x = this->x - vector.x;
		double y = this->y - vector.y;

		double x_prime = vector.x + ((x * cos(angle)) - (y * sin(angle)));
		double y_prime = vector.y + ((x * sin(angle)) + (y * cos(angle)));

		return Vector(x_prime, y_prime);
	}
}

