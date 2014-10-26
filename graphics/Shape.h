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
	void transformVerts();
	utils::Vertex transformedVerts[8];
	utils::Vertex* getVerticies();
	int* getIndicies();
	int indicies[36];
};

#endif