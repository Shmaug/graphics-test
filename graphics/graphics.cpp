#include <Windows.h>
#include <math.h>
#include "main.h"
#include "utils.h"
#include <thread>
using namespace utils;

const int maxVerticies = 21;

Vertex* verts[maxVerticies];
int* ind[maxVerticies];

Vertex* vertexBuffer[maxVerticies];
int* indexBuffer[maxVerticies];

bool indexMode = false;
static bool c = false;

static std::thread drawThread;
static bool threadInterrupt = false;


void addVertex(Vertex* vert)
{
	for (int i = 0; i < maxVerticies; i++)
	{
		if (verts[i] == NULL)
		{
			verts[i] = vert;
			break;
		}
	}
}

void addIndex(int* ind)
{
	for (int i = 0; i < maxVerticies; i++)
	{
		if (ind[i] == NULL)
		{
			ind[i] = ind;
			break;
		}
	}
}

void drawverts(HDC hdc)
{
	box(hdc,0,0,screenWidth,screenHeight,RGB(0,0,0));

	// draw verts
	for (int i = 0; i < 2; i++)
	{
		if (cV[i] != NULL)
		{
			box(hdc, cV[i]->X-2, cV[i]->Y-2, 4, 4, RGB(255,0,0));
		}
	}

	// load vertex buffer
	int c = 0;
	for (int i = 0; i < maxVerticies; i++)
	{
		if (verts[i] != NULL)
		{
			vertexBuffer[c] = verts[i];
			c++;
		}
	}
	int ci = 0;
	for (int i = 0; i < maxVerticies; i++)
	{
		if (ind[i] != NULL)
		{
			indexBuffer[ci] = ind[i];
			ci++;
		}
	}

	// draw verts
	for (int i = 0; i < maxVerticies; i+=3)
	{
		if (indexBuffer[i] != NULL)
		{
			int index = *indexBuffer[i];
			Vertex v1 = *vertexBuffer[index];
			Vertex v2 = *vertexBuffer[index+1];
			Vertex v3 = *vertexBuffer[index+2];
			line(hdc, v1.X, v1.Y, v2.X, v2.Y, RGB(0,255,0));
			line(hdc, v2.X, v2.Y, v3.X, v3.Y, RGB(0,255,0));
			line(hdc, v3.X, v3.Y, v1.X, v1.Y, RGB(0,255,0));
		}
	}
}

static void draw(HDC hdc)
{
	while(!threadInterrupt)
	{
		drawverts(hdc);
	}
}

void init(HDC hdc, HWND hwnd)
{
	drawThread = std::thread(draw, hdc);

	Vertex* vert = new Vertex(100, 100, 0);
	addVertex(vert);
	box(hdc,0,0,screenWidth,screenHeight,RGB(0,0,0));
}

Vertex* cV[3];
int cI = 0;

void mouseclick(int button, int X, int Y)
{
	switch (button)
	{
		case 2:
		{
			Vertex* vert = new Vertex();
			vert->setPos(X,Y,0);
			cV[cI] = vert;
			cI++;
			if (cI > 2)
			{
				addVertex(cV[0]);
				addVertex(cV[1]);
				addVertex(cV[2]);
				cV[0] = NULL;
				cV[1] = NULL;
				cV[2] = NULL;
				cI = 0;
			}
			return;
		}
		case 1:
		{

			return;
		}
	}
}
