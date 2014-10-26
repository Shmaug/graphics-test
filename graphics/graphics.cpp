#include <math.h>
#include "main.h"
#include <iostream>
#include <thread>
#include "Shape.h"
using namespace utils;

const int maxVerticies = 21;
const int maxIndicies = 128;

Shape cube;

Vertex vertexBuffer[maxVerticies];
int indexBuffer[maxIndicies];

bool wireframe = true;

static std::thread drawThread;
static bool threadInterrupt = false;

static float projMat[4][4];

void loadVBuffer()
{
	Vertex* v = cube.getVerticies();
	// cube
	for (int i = 0; i < 8; i++)
	{
		vertexBuffer[i] = v[i];
	}
}

void loadIBuffer()
{
	int* in = cube.getIndicies();
	for (int i = 0; i < 36; i++)
	{
		indexBuffer[i] = in[i];
	}
}

void flattenVertexBuffer()
{
	float camZ = 0;
	for (int i = 0; i < 8; i++)
	{
		float x = vertexBuffer[i].X;// / (-vertexBuffer[i].Z);
		float y = vertexBuffer[i].Y;// / (-vertexBuffer[i].Z);
		float z = vertexBuffer[i].Z;// - camZ;

		float x2 = x * projMat[0][0] + y * projMat[1][0] + z * projMat[2][0] + projMat[3][0];
        float y2 =   x * projMat[0][1] + y * projMat[1][1] + z * projMat[2][1] + projMat[3][1];
        float z2 =   x * projMat[0][2] + y * projMat[1][2] + z * projMat[2][2] + projMat[3][2];
		float w = x * projMat[0][3] + y * projMat[1][3] + z * projMat[2][3] + projMat[3][3];
		if (w != -1)
		{
			x2 /= w;
			y2 /= w;
			z2 /= w;
		}
		
		x2 *= 1e2;
		y2 *= 1e2;

		x2 += getScreenWidth()/2;
		y2 += getScreenHeight()/2;

		vertexBuffer[i].X = x2;
		vertexBuffer[i].Y = y2;
		vertexBuffer[i].Z = z2;
	}
}

Vertex cV[3];
int cI = 0;

void drawverts(HDC hdc)
{
	// clear screen
	LPPAINTSTRUCT ps = LPPAINTSTRUCT();
	BeginPaint(gethwnd(), ps);
	SelectObject(hdc, CreateSolidBrush(RGB(0,0,0)));
	Rectangle(hdc, 0, 0, getScreenWidth(), getScreenHeight());
	EndPaint(gethwnd(), ps);

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
	loadVBuffer();
	flattenVertexBuffer();

	// draw verts
	for (int i = 0; i < maxIndicies; i+=3)
	{
		if (indexBuffer[i] >= 0)
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
	int farpl = 10000;
	int nearpl = 10;

	projMat[0][0] = projMat[1][1] = (float)1/tan(35 * PI / 180);
	projMat[2][2] = -farpl/(farpl-nearpl);
	projMat[3][2] = -farpl * nearpl / (farpl-nearpl);
	projMat[2][3] = -1;
	projMat[3][3] = 0;

	drawThread = std::thread(draw, std::ref(hdc));

	cube = Shape();
	cube.MakeCube();
	cube.transform.SX = 100;
	cube.transform.SY = 100;
	cube.transform.SZ = 100;

	cube.transform.TX = 0;
	cube.transform.TY = 0;
	cube.transform.TZ = 100;
	cube.transformVerts();

	loadIBuffer();
} 

void mouseclick(int button, int X, int Y)
{
	switch (button)
	{
		case 2:
		{

			return;
		}
		case 1:
		{

			return;
		}
	}
}
