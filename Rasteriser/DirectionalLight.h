#pragma once
#include "Vector3D.h"
#include "Light.h"

class DirectionalLight : public Light
{
public:
	//COnstructors
	DirectionalLight();
	DirectionalLight(int r, int g, int b, Vector3D direction);
	//Destructor
	~DirectionalLight();
	//Copy Constructor
	DirectionalLight(const DirectionalLight &v);
	//Accessors
	Vector3D GetDirection() const;
	void SetDirection(const Vector3D direction);

private:
	Vector3D _direction;
};