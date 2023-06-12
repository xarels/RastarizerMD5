#include "PointLight.h"

PointLight::PointLight() : Light ()
{
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
	_lightSource = Vertex(0, 0, 0);
	_atten_distance = 0;
	_atten_a = 0;
	_atten_b = 0;
	_atten_c = 0;
}

PointLight::PointLight(int r, int g, int b, Vertex lightSource, float atten_a, float atten_b, float atten_c) : Light(r,g,b)
{
	_r = (float) r;
	_g = (float) g;
	_b = (float) b;
	_lightSource = lightSource;
	_atten_a = atten_a;
	_atten_b = atten_b;
	_atten_c = atten_c;
}

PointLight::~PointLight()
{
}

PointLight::PointLight(const PointLight &v) : Light(v)
{
	_r = v._r;
	_g = v._g;
	_b = v._b;
	_lightSource = v._lightSource;
	_atten_distance = v._atten_distance;
	_atten_a = v._atten_a;
	_atten_b = v._atten_b;
	_atten_c = v._atten_c;
}

Vertex PointLight::GetLightSource() const
{
	return _lightSource;
}

void PointLight::SetLightSource(const Vertex point)
{
	_lightSource = point;
}

int PointLight::GetAttenDistance() const
{
	return _atten_distance;
}

void PointLight::SetAttenDistance(const int atten_D)
{
	_atten_distance = atten_D;
}

int PointLight::GetAttenA() const
{
	return _atten_a;
}

void PointLight::SetAttenA(const int atten_A)
{
	_atten_a = atten_A;
}

int PointLight::GetAttenB() const
{
	return _atten_b;
}

void PointLight::SetAttenB(const int atten_B)
{
	_atten_b = atten_B;
}

int PointLight::GetAttenC() const
{
	return _atten_c;
}

void PointLight::SetAttenC(const int atten_C)
{
	_atten_c = atten_C;
}
