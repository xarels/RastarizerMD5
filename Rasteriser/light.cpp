#include "Light.h"

Light::Light()
{
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
}

Light::Light(int r, int g, int b)
{
	_r = (float) r;
	_g = (float) g;
	_b = (float) b;
}

Light::~Light()
{
}

Light::Light(const Light &v)
{
	_r = v._r;
	_g = v._g;
	_b = v._b;
}


float Light::GetRColor() const
{
	return _r;
}

void Light::SetRColor(const float r)
{
	_r = r;
}

float Light::GetGColor() const
{
	return _g;
}

void Light::SetGColor(const float g)
{
	_g = g;
}

float Light::GetBColor() const
{
	return _b;
}

void Light::SetBColor(const float b)
{
	_b = b;
}