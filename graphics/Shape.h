#include "Matrix.h"
#include "utils.h"

#ifndef SHAPE
#define SHAPE

class Shape
{
private:
	utils::Vertex verts[8];
	int indicies[36];
	utils::Vertex transformedVerts[8];
public:
	Matrix transform;
	Shape();
	void MakeCube();
	void transformVerts();
	utils::Vertex* getVerticies();
	int* getIndicies();
};

#endif