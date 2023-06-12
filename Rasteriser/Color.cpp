#include "Color.h"
#include "Color.h"



Color::Color()
{
	_color = RGB(0, 0, 0);
}


Color::~Color()
{
}

Color::Color(const Color& v)
{
	_color = v._color;
}

COLORREF Color::GetColor() const
{
	return _color;
}

void Color::SetColor(const float r, const float g, const float b)
{
	_color = RGB(r, g, b);
}

int Color::GetRed() const
{
	return GetRValue(_color);
}

int Color::GetGreen() const
{
	return GetGValue(_color);
}

int Color::GetBlue() const
{
	return GetBValue(_color);
}
