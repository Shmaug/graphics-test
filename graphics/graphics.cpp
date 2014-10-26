#include <math.h>
#include "main.h"
#include "utils.h"
#include <iostream>
#include <thread>
#include "Shape.h"
using namespace utils;

const int maxVerticies = 21;
const int maxIndicies = 128;

Shape cube;

Vertex verts[maxVerticies] = {Vertex()};
int ind[maxIndicies] = {-1};

Vertex vertexBuffer[maxVerticies];
int indexBuffer[maxIndicies];

bool wireframe = true;

static std::thread drawThread;
static bool threadInterrupt = false;

int addVertex(Vertex vert)
{
	int in;
	for (int i = 0; i < maxVerticies; i++)
	{
		if (!verts[i].initialized)
		{
			verts[i] = vert;
			in = i;
			break;
		}
	}
	return in;
}

void addIndex(int in)
{
	for (int i = 0; i < maxVerticies; i++)
	{
		if (ind[i] == -1)
		{
			ind[i] = in;
			break;
		}
	}
}

void flattenVertexBuffer()
{
	
}

Vertex cV[3];
int cI = 0;

void drawverts(HDC hdc)
{
	if (threadInterrupt) { return; }

	// draw cVerts
	for (int i = 0; i < 3; i++)
	{
		if (cV[i].initialized)
		{
			box(hdc, cV[i].X-2, cV[i].Y-2, 4, 4, RGB(255,0,0));
		}
	}
	if (threadInterrupt) { return; }

	// load vertex buffer
	int c = 0;
	for (int i = 0; i < maxVerticies; i++)
	{
		if (verts[i].initialized)
		{
			vertexBuffer[c] = verts[i];
			c++;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		vertexBuffer[c] = cube.verts[i];
		c++;
	}
	if (threadInterrupt) { return; }
	int ci = 0;
	for (int i = 0; i < maxIndicies; i++)
	{
		if (ind[i] != -1)
		{
			indexBuffer[ci] = ind[i];
			ci++;
		}
	}
	if (threadInterrupt) { return; }
	flattenVertexBuffer();
	// draw verts
	for (int i = 0; i < maxIndicies; i+=3)
	{
		if (indexBuffer[i] != -1)
		{
			int index = indexBuffer[i];
			Vertex v1 = vertexBuffer[index];
			Vertex v2 = vertexBuffer[index+1];
			Vertex v3 = vertexBuffer[index+2];
			box(hdc, v1.X-2,v1.Y-2,4,4,RGB(0,0,255));
			box(hdc, v2.X-2,v2.Y-2,4,4,RGB(0,0,255));
			box(hdc, v3.X-2,v3.Y-2,4,4,RGB(0,0,255));
			if (wireframe)
			{
				line(hdc, v1, v2);
				line(hdc, v2, v3);
				line(hdc, v3, v1);
			}
			else

			{
				int top = min(v1.Y,min(v2.Y,v3.Y));
				int left = min(v1.X,min(v2.X,v3.X));
				int bottom = max(v1.Y,max(v2.Y,v3.Y));
				int right = max(v1.X,max(v2.X,v3.X));
				for (int x = left; x < right; x++)
				{
					for (int y = top; y < bottom; y++)
					{
						float alpha = 0;
						float beta = 0;
						float gamma = 0;
						if (pointInTriangle(x, y, v1, v2, v3, alpha, beta, gamma))
						{
							SetPixel(hdc, x, y, v1.color*alpha + v2.color*beta + v3.color*gamma);
						}
					}
				}
			}
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
	drawThread = std::thread(draw, std::ref(hdc));

	cube = Shape();
	cube.MakeCube();
} 

void mouseclick(int button, int X, int Y)
{
	switch (button)
	{
		case 2:
		{
			Vertex vert = Vertex();
			vert.setPos(X,Y,0);
			cV[cI] = vert;
			cI++;
			if (cI > 2)
			{
				int i1 = addVertex(cV[0]);
				int i2 = addVertex(cV[1]);
				int i3 = addVertex(cV[2]);
				cV[0] = Vertex();
				cV[1] = Vertex();
				cV[2] = Vertex();
				cI = 0;

				addIndex(i1);
				addIndex(i2);
				addIndex(i3);
			}
			return;
		}
		case 1:
		{

			return;
		}
	}
}
