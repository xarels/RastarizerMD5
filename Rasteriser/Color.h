#pragma once
#include <Windows.h>
class Color
{
public:
	Color();
	~Color();
	Color(const Color& v);

	COLORREF GetColor() const;
	void SetColor(const float r, const float g, const float b);

	int GetRed() const;
	int GetGreen() const;
	int GetBlue() const;

private:
	COLORREF _color;
};

