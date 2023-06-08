#include "Vector3D.h"

Vector3D::Vector3D()
{
	_vX = 0.0f;
	_vY = 0.0f;
	_vZ = 0.0f;
	_length = 0.0f;
}

Vector3D::Vector3D(float x, float y)
{
	_vX = x;
	_vY = y;
}

Vector3D::Vector3D(float vectorX, float vectorY, float vectorZ)
{
	_vX = vectorX;
	_vY = vectorY;
	_vZ = vectorZ;
}


Vector3D::~Vector3D()
{
}

Vector3D::Vector3D(const Vector3D & v)
{
	_vX = v.GetVX();
	_vY = v.GetVY();
	_vZ = v.GetVZ();
	_length = v.GetLength();
}

float Vector3D::GetVX() const
{
	return _vX;
}	

void Vector3D::SetVX(const float x)
{
	_vX = x;
}

float Vector3D::GetVY() const
{
	return _vY;
}

void Vector3D::SetVY(const float y)
{
	_vY = y;
}

float Vector3D::GetVZ() const
{
	return _vZ;
}

void Vector3D::SetVZ(const float z)
{
	_vZ = z;
}

const float Vector3D::GetLength() const
{
	return (float) sqrt(_vX * _vX +
						_vY * _vY + 
						_vZ * _vZ);
}

float Vector3D::DotProduct(const Vector3D &u, const Vector3D &v)
{
	return  u._vX * v.GetVX() +
			u._vY * v.GetVY() +
			u._vZ * v.GetVZ();
}

Vector3D Vector3D::CrossProduct(const Vector3D &u, const Vector3D &v)
{
	return Vector3D(u.GetVY() * v.GetVZ() - u.GetVZ() * v.GetVY(),
		u.GetVZ() * v.GetVX() - u.GetVX() * v.GetVZ(),
		u.GetVX() * v.GetVY() - u.GetVY()* v.GetVX());
}

float Vector3D::CrossProductBarycentric(const Vector3D &u, const Vector3D &v)
{
	return (u.GetVX() * v.GetVY() - u.GetVY() * v.GetVX());
}


Vector3D& Vector3D::operator= (const Vector3D& rhs)
{
	if (this != &rhs)
	{
		_vX = rhs.GetVX();
		_vY = rhs.GetVY();
		_vZ = rhs.GetVZ();
		_length = rhs.GetLength();
	}
	return *this;
}

bool Vector3D::operator== (const Vector3D& rhs) const
{
	return (_vX == rhs.GetVX() && _vY == rhs.GetVY() && _vZ == rhs.GetVZ());
}

Vector3D Vector3D::operator+ (const Vector3D& rhs) const
{
	return Vector3D(_vX + rhs.GetVX(), _vY + rhs.GetVY(), _vZ + rhs.GetVZ());
}

Vector3D Vector3D::operator/ (const int rhs) const
{
	return Vector3D(_vX / rhs, _vY / rhs, _vZ / rhs);
}

void Vector3D::NormaliseVector3D()
{
	_length = GetLength();

	if (_length == 0)
	{
		return;
	}

	_vX = _vX / _length;
	_vY = _vY / _length;
	_vZ = _vZ / _length;
}