#include "Vertex.h"
#include "Vector3D.h"

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 0.0f;
	_normal = Vector3D(0, 0, 0);
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
	_contributed = 0;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1.0f;
	_normal = Vector3D(0, 0, 0);
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
	_contributed = 0;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
	_normal = Vector3D(0, 0, 0);
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
	_contributed = 0;
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1.0f;
	_normal = Vector3D(0, 0, 0);
	_r = r;
	_g = g;
	_b = b;
	_contributed = 0;
}

Vertex::Vertex(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
	_normal = v.GetNormal();
	_r = v.GetRColor();
	_g = v.GetGColor();
	_b = v.GetBColor();
	_contributed = v.GetContributionCount();
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

Vertex& Vertex::operator=(const Vertex& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
		_normal = rhs.GetNormal();
		_r = rhs.GetRColor();
		_g = rhs.GetGColor();
		_b = rhs.GetBColor();
		_contributed = rhs.GetContributionCount();
	}
	return *this;
}

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ(), _w + rhs.GetW());
}

Vector3D Vertex::operator-(const Vertex& rhs) const
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
	return count;
}

void Vertex::SetContributionCount(const int i)
{
	count = i;
}

int Vertex::CountContribution()
{
	return count++;
}
