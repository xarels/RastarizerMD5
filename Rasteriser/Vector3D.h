#pragma once
#include <math.h>

class Vector3D
{
public:
	//Constructor
	Vector3D();
	Vector3D(float x, float y);
	Vector3D(float x, float y, float z);

	//Destructor
	~Vector3D();

	//Copy Constructor
	Vector3D(const Vector3D& v);

	//Accessors
	float GetVX() const;
	void SetVX(const float x);
	float GetVY() const;
	void SetVY(const float y);
	float GetVZ() const;
	void SetVZ(const float z);
	const float GetLength() const;

	//Equations
	static float DotProduct(const Vector3D& u, const Vector3D& v);
	static Vector3D CrossProduct(const Vector3D& u, const Vector3D& v);
	static float CrossProductBarycentric(const Vector3D & u, const Vector3D & v);

	//Operators
	Vector3D& operator= (const Vector3D& rhs);
	bool operator== (const Vector3D& rhs) const;
	Vector3D operator+ (const Vector3D& rhs) const;
	Vector3D operator/ (const int rhs) const;

	//Normalise Vector
	void NormaliseVector3D();

private:
	float _vX;
	float _vY;
	float _vZ;
	float _length;
};