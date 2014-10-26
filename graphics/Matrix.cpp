#include "Matrix.h"
#include <math.h>;

float R11, R12, R13, TX,
	  R21, R22, R23, TY,
	  R31, R32, R33, TZ,
	  SX,  SY,  SZ,  S;

Matrix::Matrix()
{
	R11, R12, R13, TX, R21, R22, R23, TY, R31, R32, R33, TZ, SX, SY, SZ, S = 0;
	R11, R22, R33, S = 1;
}

void Matrix::SetPosition(float x, float y, float z)
{
	TX = x;
	TY = y;
	TZ = z;
}

utils::Vertex Matrix::Multiply(utils::Vertex vert)
{
	// apply rotation
	float x = vert.X;
	float y = vert.Y;
	float z = vert.Z;
	// apply scale
	x *= SX;
	y *= SY;
	z *= SZ;
	// apply transformation
	x += TX;
	y += TY;
	z += TZ;

	utils::Vertex v = utils::Vertex(x, y, z, vert.color);
	return v;
}

void Matrix::Translate(float x, float y, float z)
{
	TX += x;
	TY += y;
	TZ += z;
}
// rotate
void Matrix::SetRotation(float x, float y, float z)
{

}

void Matrix::Rotate(float x, float y, float z)
{
	SetRotation(x, y, z);
}
// scale
void Matrix::SetScale(float x, float y, float z)
{
	SX = x;
	SY = y;
	SZ = z;
}

void Matrix::Scale(float x, float y, float z)
{
	SX *= x;
	SY *= y;
	SZ *= z;
}