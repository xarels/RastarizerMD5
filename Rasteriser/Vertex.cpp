#include "Vertex.h"
#include "Vector3D.h"

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1.0f;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1.0f;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

Vertex::Vertex(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
}

Vertex::~Vertex()
{
}

float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetZ() const
{
	return _z;
}
void Vertex::SetZ(const float z)
{
	_z = z;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

Vector3D Vertex::GetNormal() const
{
	return _normal;
}

void Vertex::SetNormal(const Vector3D normal)
{
	_normal = normal;
}

float Vertex::GetRColor() const
{
	return _r;
}

void Vertex::SetRColor(const float r)
{
	_r = r;
}

float Vertex::GetGColor() const
{
	return _g;
}

void Vertex::SetGColor(const float g)
{
	_g = g;
}

float Vertex::GetBColor() const
{
	return _b;
}

void Vertex::SetBColor(const float b)
{
	_b = b;
}

int Vertex::GetContributionCount() const
{
	return _contributed;
}
 
void Vertex::SetContributionCount(const int i)
{
	_contributed = i;
}

int Vertex::CountContribution()
{
	return count++;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
	}
	return *this;
}

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(),_z + rhs.GetZ(), _w + rhs.GetW());
}

Vector3D Vertex::operator-(const Vertex & rhs) const
{
	return Vector3D(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

void Vertex::dehomogenizeVertices()
{
	if (_w == 0)
	{
		return;
	}

	_x = _x / _w;
	_y = _y / _w;
	_z = _z / _w;
	_w = 1.0f;
}