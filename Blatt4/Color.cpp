#include "Color.h"
using namespace std;
Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}
Color::Color(int r, int g, int b)
{
	if (r < 0 || r>255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		throw logic_error("value is outside of range");
	}
	red = r;
	green = g;
	blue = b;
}
int Color::getRed()
{
	return red;
}
int Color::getGreen()
{
	return green;
}
int Color::getBlue()
{
	return blue;
}
void Color::setRed(int r)
{
	if (r < 0 || r > 255)
		throw logic_error("value is out  of range");
	red = r;
}
void Color::setGreen(int g)
{
	if (g< 0 || g> 255)
		throw logic_error("value is out  of range");
	green = g;
}
void Color::setBlue(int b)
{
	if (b< 0 ||b> 255)
		throw logic_error("value is out  of range");
	blue = b;
}
Color Color::darken(int amount)
{
	if (amount < 0)
		amount = 0;
	red -= amount;
	red = red < 0 ? 0 : red;

	green -= amount;
	green = green < 0 ? 0 : green;

	blue -= amount;
	blue = blue < 0 ? 0 : blue;

	Color color(red, green, blue);

	return color;

}

Color Color::lighten(int amount)
{
	if(amount < 0)
		amount = 0;

	red += amount;
	red = red > 255 ? 255 : red;

	green += amount;
	green = green > 255 ? 255 : green;

	blue += amount;
	blue = blue > 255 ? 255 : blue;

	Color color(red, green, blue);
	return color;
}

