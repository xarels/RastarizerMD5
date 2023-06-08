#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	_direction = Vector3D(0, 0, 0);
}

DirectionalLight::DirectionalLight(int r, int g, int b, Vector3D direction) : Light (r, g, b)
{
	_direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}

DirectionalLight::DirectionalLight(const DirectionalLight & v) : Light(v)
{
	_direction = v._direction;
}

Vector3D DirectionalLight::GetDirection() const
{
	return _direction;
}

void DirectionalLight::SetDirection(const Vector3D direction)
{
	_direction = direction;
}