#pragma once

class Light
{
public:
	Light();
	Light(int r, int g, int b);
	~Light();
	Light(const Light &v);

	//Accessors
	float GetRColor() const;
	void SetRColor(const float r);
	float GetGColor() const;
	void SetGColor(const float g);
	float GetBColor() const;
	void SetBColor(const float b);

protected:
	float _r;
	float _g;
	float _b;
};