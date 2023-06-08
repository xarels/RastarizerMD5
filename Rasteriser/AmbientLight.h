#pragma once
#include "Light.h"

class AmbientLight  : public Light 
{
public:
	AmbientLight();
	AmbientLight(int r, int g, int b);
	~AmbientLight();
	AmbientLight(const AmbientLight &v);
private:
};