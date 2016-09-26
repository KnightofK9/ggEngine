#include "Vector3.h"

	Vector3::Vector3()
	{
		this->x = this->y = this->z = 0;
	}
	Vector3::Vector3(const Vector3 & v)
	{
		*this = v;
	}
	Vector3::Vector3(double x, double y, double z)
	{
		Set(x, y, z);
	}
	Vector3::Vector3(int x, int y, int z)
	{
		Set((double)x, (double)y, (double)z);
	}
	void Vector3::Set(double x1, double y1, double z1)
	{
		this->x = x1;
		this->y = y1;
		this->z = z1;
	}
	void Vector3::Set(const Vector3 & v)
	{
		*this = v;
	}
	void Vector3::Move(double mx, double my, double mz)
	{
		this->x += mx;
		this->y += my;
		this->z += mz;
	}
	void Vector3::operator+=(const Vector3 & v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}
	void Vector3::operator-=(const Vector3 & v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}
	void Vector3::operator*=(const Vector3 & v)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
	}
	void Vector3::operator/=(const Vector3 & v)
	{
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
	}
	bool Vector3::operator==(const Vector3 & v) const
	{
		return (
			(((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
			(((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))) &&
			(((v.z - 0.0001f) < z) && (z < (v.z + 0.0001f))));
	}
	bool Vector3::operator!=(const Vector3 & p) const
	{
		return (!(*this == p));
	}
	Vector3 & Vector3::operator=(const Vector3 & v)
	{
		Set(v);
		return *this;
	}
	double Vector3::Distance(const Vector3 & v)
	{
		return sqrt((v.x - x)*(v.x - x) + (v.y - y)*(v.y - y));
	}
	double Vector3::Length()
	{
		return sqrt(x*x + y*y + z*z);
	}
	double Vector3::DotProduct(const Vector3 & v)
	{
		return (x*v.x + y*v.y + z*v.z);
	}
	Vector3 Vector3::CrossProduct(const Vector3 & v)
	{
		double nx = (y*v.z) - (z*v.y);
		double ny = (z*v.y) - (x*v.z);
		double nz = (x*v.y) - (y*v.x);
		return Vector3(nx, ny, nz);
	}
	Vector3 Vector3::Normal()
	{
		double length;
		if (Length() == 0)
			length = 0;
		else
			length = 1 / Length();
		double nx = x*length;
		double ny = y*length;
		double nz = z*length;
		return Vector3(nx, ny, nz);
	}
