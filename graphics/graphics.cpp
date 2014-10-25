#include <Windows.h>
#include <math.h>
#include "main.h"
#include "utils.h"
#include <thread>
using namespace utils;

const int maxVerticies = 21;

Vertex* mouseVerts[maxVerticies];
int* mouseIndicies[maxVerticies];

Vertex* vertexBuffer[maxVerticies];
int* indexBuffer[maxVerticies];

bool indexMode = false;
static bool c = false;

std::thread drawThread;


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

void drawverts(HDC hdc)
{
	box(hdc,0,0,screenWidth,screenHeight,RGB(0,0,0));

	box(hdc,200,200,200,200,RGB(255,0,255));
	// draw verts
	for (int i = 0; i < maxVerticies; i++)
	{
		if (mouseVerts[i] != NULL)
		{
			box(hdc, mouseVerts[i]->X-5, mouseVerts[i]->Y-5, 10, 10, RGB(0,255,0));
		}
	}
	// draw line for vert mode

	/*
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
	}*/
}

void draw(HDC *hdc)
{
	while(true)
	{
		drawverts(*hdc);
	}
}

void init(HDC hdc, HWND hwnd)
{
	drawThread = std::thread(draw, hdc);


	Vertex* vert = new Vertex(100, 100, 0);
	addVertex(vert);
	box(hdc,0,0,screenWidth,screenHeight,RGB(0,0,0));
}

void mouseclick(int button, int X, int Y)
{
	switch (button)
	{
		case 2:
		{
			Vertex* vert = new Vertex();
			vert->setPos(X,Y,0);
			addVertex(vert);
			return;
		}
		case 1:
		{
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
		}
	}
}
