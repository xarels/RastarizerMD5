#pragma once
#include "Vector3D.h"

class Vertex
{
public:
	//Constructors
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float w);
 
	//Copy Constructor
	Vertex(const Vertex& v);

	//Destructor
	~Vertex();

	//Accessors
	float GetX() const;
	void SetX(const float x);

	float GetY() const;
	void SetY(const float y);

	float GetZ() const;
	void SetZ(const float z);

	float GetW() const;
	void SetW(const float w);

	Vector3D GetNormal() const;
	void SetNormal(const Vector3D normal);

	float GetRColor() const;
	void SetRColor(const float r);

	float GetGColor() const;
	void SetGColor(const float g);

	float GetBColor() const;
	void SetBColor(const float b);

	int GetContributionCount() const;
	void SetContributionCount(const int i);
	int CountContribution();

	//Operators
	Vertex& operator= (const Vertex& rhs);
	bool operator== (const Vertex& rhs) const;
	Vertex operator+ (const Vertex& rhs) const;
	Vector3D operator-(const Vertex& rhs) const;

	//Dehomogenize vertices
	void dehomogenizeVertices();

private:
	float _x;
	float _y;
	float _z;
	float _w;
	float _r;
	float _g;
	float _b;
	int _contributed;
	Vector3D _normal;
	int count;
};