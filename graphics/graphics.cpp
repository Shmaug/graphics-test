#include <Windows.h>
#include <math.h>
#include "main.h"
#include "utils.h"
using namespace utils;

const int maxMouseVerts = 2048;
Vertex* mouseVerts[maxMouseVerts];

const int vertexBufferSize = 2048;
Vertex* vertexBuffer[vertexBufferSize];

void addVertex(Vertex* vert)
{
	for (int i = 0; i < maxMouseVerts; i++)
	{
		if (mouseVerts[i] == NULL)
		{
			mouseVerts[i] = vert;
			break;
		}
	}
}

void draw(HDC hdc)
{
	int c = 0;
	for (int i = 0; i < maxMouseVerts; i++)
	{
		if (mouseVerts[i] != NULL)
		{
			vertexBuffer[c] = mouseVerts[i];
			c++;
		}
	}

	for (int i = 0; i < vertexBufferSize; i++)
	{
		SetPixel(hdc, (int) vertexBuffer[i]->X, (int) vertexBuffer[i]->Y, RGB(0,0,0));
		vertexBuffer[i] = NULL;
	}
}

void mousemove(int X, int Y)
{
	Vertex* vert = new Vertex(X,Y,0);
	addVertex(vert);
}
