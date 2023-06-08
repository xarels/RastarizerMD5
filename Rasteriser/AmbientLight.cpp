#include "AmbientLight.h"

AmbientLight::AmbientLight() : Light ()
{

}

AmbientLight::AmbientLight(int r, int g, int b) : Light (r,g,b)
{
}

AmbientLight::~AmbientLight()
{
}

AmbientLight::AmbientLight(const AmbientLight &v) : Light (v)
{
}