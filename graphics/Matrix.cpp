#include "Matrix.h"
#include <math.h>;

float R11, R12, R13, TX,
	  R21, R22, R23, TY,
	  R31, R32, R33, TZ,
	  SX,  SY,  SZ,  S;

float mat[4][4];

void updateMat()
{
	mat[0][0] = R11;
	mat[1][0] = R12;
	mat[2][0] = R13;
	mat[3][0] = TX;

	mat[0][1] = R21;
	mat[1][1] = R22;
	mat[2][1] = R23;
	mat[3][1] = TY;

	mat[0][2] = R31;
	mat[1][2] = R32;
	mat[2][2] = R33;
	mat[3][2] = TZ;

	mat[0][3] = SX;
	mat[1][3] = SY;
	mat[2][3] = SZ;
	mat[3][3] = S;
}

Matrix::Matrix()
{
	R11, R12, R13, TX, R21, R22, R23, TY, R31, R32, R33, TZ, SX, SY, SZ, S = 0;
	R11, R22, R33, S = 1;
	updateMat();
}

void Matrix::SetPosition(float x, float y, float z)
{
	TX = x;
	TY = y;
	TZ = z;
}

utils::Vertex Matrix::Multiply(utils::Vertex vert)
{
	updateMat();

	float x1 = vert.X;
	float y1 = vert.Y;
	float z1 = vert.Z;

	// apply rotation
	float x = x1;//mat[0][0]*x1 + mat[0][1]*y1 + mat[0][2]*z1;
	float y = y1;//mat[1][0]*x1 + mat[1][1]*y1 + mat[1][2]*z1;
	float z = z1;//mat[2][0]*x1 + mat[2][1]*y1 + mat[2][2]*z1;
	// apply scale
	x *= SX;
	y *= SY;
	z *= SZ;
	// apply transformation
	x += TX;
	y += TY;
	z += TZ;

	utils::Vertex v = utils::Vertex(x,y,z, vert.color);
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
	R11=cos(y) * cos(z);
	R12=-sin(z) * cos(y);
	R13=sin(y);
	R21=cos(z) * sin(y) * sin(x) + sin(z) * cos(x);
	R22=cos(z) * cos(x) - sin(z) * sin(y) * sin(x);
	R23=-cos(y)*sin(x);
	R31=sin(z) * sin(x) - cos(z) * sin(y) * cos(x);
	R32=sin(z) * sin(y) * cos(x) + cos(z) * sin(x);
	R33=sin(z) * sin(y) * cos(x) + cos(z) * sin(x);
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