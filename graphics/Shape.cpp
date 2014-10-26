#include "Shape.h"
using namespace utils;

Vertex verts[];
int indicies[];
Matrix transform;
Shape::Shape()
{
	transform = Matrix();
}

void Shape::MakeCube()
{
	Vertex verts[8];
	int indicies[36];

	verts[0] = Vertex(-.5, .5, .5, RGB(0,255,0));
	verts[1] = Vertex(.5, .5, .5, RGB(0,255,0));
	verts[2] = Vertex(.5, .5, -.5, RGB(0,255,0));
	verts[3] = Vertex(-.5, .5, -.5, RGB(0,255,0));
	
	verts[4] = Vertex(-.5, -.5, .5, RGB(255,0,0));
	verts[5] = Vertex(.5, -.5, .5, RGB(255,0,0));
	verts[6] = Vertex(.5, -.5, -.5, RGB(255,0,0));
	verts[7] = Vertex(-.5, - .5, -.5, RGB(255,0,0));
	
	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;//top face
	indicies[3] = 1;
	indicies[4] = 3;
	indicies[5] = 2;

	indicies[6] = 5;
	indicies[7] = 4;
	indicies[8] = 6;//bottom face
	indicies[9] = 4;
	indicies[10] = 7;
	indicies[11] = 6;

	indicies[12] = 2;
	indicies[13] = 3;
	indicies[14] = 7;//front face
	indicies[15] = 3;
	indicies[16] = 6;
	indicies[17] = 7;

	indicies[18] = 1;
	indicies[19] = 0;
	indicies[20] = 5;//back face
	indicies[21] = 0;
	indicies[22] = 4;
	indicies[23] = 5;

	indicies[24] = 0;
	indicies[25] = 2;
	indicies[26] = 4;//left face
	indicies[27] = 2;
	indicies[28] = 4;
	indicies[29] = 7;

	indicies[30] = 3;
	indicies[31] = 1;
	indicies[32] = 6;//right face
	indicies[33] = 1;
	indicies[34] = 5;
	indicies[35] = 6;
}
