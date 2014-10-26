#include "Matrix.h"
#include "utils.h"
#ifndef SHAPE
#define SHAPE

class Shape
{
public:
	Matrix transform;
	Shape();
	void MakeCube();
	utils::Vertex verts[8];
	int indicies[];
};

#endif