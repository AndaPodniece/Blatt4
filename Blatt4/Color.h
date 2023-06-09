#pragma once
#include <stdexcept>

class Color
{
public:
	Color();
	Color(int r, int g, int b);
	int getRed();
	int getGreen();
	int getBlue();
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);

	Color darken(int amount);
	Color lighten(int amount);

	
	
private:
	int red;
	int green;
	int blue;
};