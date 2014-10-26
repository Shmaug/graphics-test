#include "utils.h"
#include <math.h>

using namespace utils;

COLORREF color;

float X, Y, Z;
bool initialized = false;

void Vertex::setPos(float x, float y, float z)
{
	X=x;
	Y=y;
	Z=z;
	initialized = true;
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
	initialized = true;
}

Vertex::Vertex(float x, float y, float z, COLORREF color)
{
	setPos(x,y,z);
	color = color;
	initialized = true;
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

void line(HDC hdc, Vertex v1, Vertex v2)
{
	int xmin,ymin,xmax,ymax=0;
	if (v1.X < v2.X)
	{
		xmin = v1.X;
		ymin = v1.Y;
		xmax = v2.X;
		ymax = v2.Y;
	}
	else
	{
		xmin = v2.X;
		ymin = v2.Y;
		xmax = v1.X;
		ymax = v1.Y;
	}
	float xdist = xmax-xmin;
	float ydist = ymax-ymin;
	float dist = sqrt(pow(xdist,2) + pow(ydist,2));
	for (int i = 0; i < dist; i++)
	{
		float d = i/(float)dist;
		float x=xdist*d;
		float y=ydist*d;

		SetPixel(hdc, xmin+x, ymin+y, v1.color);
	}
}

bool pointInTriangle(int x, int y, Vertex p1, Vertex p2, Vertex p3, _Inout_ float alpha, _Inout_ float beta, _Inout_ float gamma)
{
	alpha = ((p2.Y - p3.Y)*(x - p3.X) + (p3.X - p2.X)*(y - p3.Y)) /
        ((p2.Y - p3.Y)*(p1.X - p3.X) + (p3.X - p2.X)*(p1.Y - p3.Y));
	beta = ((p3.Y - p1.Y)*(x - p3.X) + (p1.X - p3.X)*(y - p3.Y)) /
       ((p2.Y - p3.Y)*(p1.X - p3.X) + (p3.X - p2.X)*(p1.Y - p3.Y));
	gamma = 1.0f - alpha - beta;
	if (alpha > 0 && beta > 0 && gamma > 0)
		return true;
	else
		return false;
}