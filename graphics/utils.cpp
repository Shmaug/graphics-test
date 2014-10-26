#include "utils.h"

using namespace utils;

COLORREF color;

float X, Y, Z;

void Vertex::setPos(float x, float y, float z)
{
	X=x;
	Y=y;
	Z=z;
}

Vertex::Vertex()
{
	X,Y,Z = 0;
	color = RGB(0,255,0);
}

Vertex::Vertex(float x, float y, float z)
{
	setPos(x,y,z);
	color = RGB(0,255,0);
}

Vertex::Vertex(float x, float y, float z, COLORREF color)
{
	setPos(x,y,z);
	color = color;
}

void box(HDC hdc, int x, int y, int w, int h, COLORREF color)
{
	for (int j = x; j < x+w; j++)
	{
		for (int k = y; k < y+h; k++)
		{
			SetPixel(hdc, j, k, color);
		}
	}
}

void line(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{

}