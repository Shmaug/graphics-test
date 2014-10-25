#include <Windows.h>
#include <math.h>
#include "main.h"
#include "utils.h"
#include <ctime>
using namespace utils;

const int maxVerticies = 64*3;

Vertex* mouseVerts[maxVerticies];
int* mouseIndicies[maxVerticies];

Vertex* vertexBuffer[maxVerticies];
int* indexBuffer[maxVerticies];

bool indexMode = false;
bool c = false;

float deltaTime = 0;

void addVertex(Vertex* vert)
{
	for (int i = 0; i < maxVerticies; i++)
	{
		if (mouseVerts[i] == NULL)
		{
			mouseVerts[i] = vert;
			break;
		}
	}
}

void addIndex(int* ind)
{
	for (int i = 0; i < maxVerticies; i++)
	{
		if (mouseIndicies[i] == NULL)
		{
			mouseIndicies[i] = ind;
			break;
		}
	}
}

void draw(HDC hdc)
{
	// clear screen
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (c)
			SetPixel(hdc, i, j, RGB(0,255,0));
			else
			SetPixel(hdc, i, j, RGB(0,0,0));
		}
	}

	// draw verts
	for (int i = 0; i < maxVerticies; i++)
	{
		if (mouseVerts[i] != NULL)
		{
			for (int j = -5; j < 5; j++)
			{
				for (int k = -5; k < 5; k++)
				{
				SetPixel(hdc, (int) vertexBuffer[i]->X + j, (int) vertexBuffer[i]->Y + k, RGB(255,0,0));
				}
			}
		}
	}
	// draw line for vert mode


	// draw triangles
	int c = 0;
	for (int i = 0; i < maxVerticies; i++)
	{
		if (mouseVerts[i] != NULL)
		{
			vertexBuffer[c] = mouseVerts[i];
			c++;
		}
	}

	for (int i = 0; i < maxVerticies; i++)
	{
		if (vertexBuffer[i] != NULL)
		{
			SetPixel(hdc, (int) vertexBuffer[i]->X, (int) vertexBuffer[i]->Y, RGB(0,0,0));
			vertexBuffer[i] = NULL;
		}
	}
}

void mouseclick(int button, int X, int Y)
{
	switch (button)
	{
	case 1:
		if (!indexMode)
			indexMode = true;
		int* index;
		for (int i = 0; i < maxVerticies; i++)
		{
			if (abs(mouseVerts[i]->X - X) < 4 && abs(mouseVerts[i]->Y - Y) < 4)
			{
				index = &i;
				break;
			}
		}
		addIndex(index);
		return;
	case 0:
		c = true;
		Vertex* vert = new Vertex();
		vert->setPos(X,Y,0);
		addVertex(vert);
		return;
	}
}
