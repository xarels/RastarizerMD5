#pragma once
#include "PointLight.h"
#include <math.h>
#include "Vertex.h"
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(int r, int g, int b, Vertex lightSource, float atten_a, float atten_b, float atten_c);
	~PointLight();
	PointLight(const PointLight &v);

	Vertex GetLightSource() const;
	void SetLightSource(const Vertex point);

	int GetAttenDistance() const;
	void SetAttenDistance(const int atten_D);
	int GetAttenA() const;
	void SetAttenA(const int atten_A);
	int GetAttenB() const;
	void SetAttenB(const int atten_B);
	int GetAttenC() const;
	void SetAttenC(const int atten_C);

private:
	Vertex _lightSource;
	int _atten_distance;
	int _atten_a;
	int _atten_b;
	int _atten_c;
};