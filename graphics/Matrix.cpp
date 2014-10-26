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

void Matrix::Translate(float x, float y, float z)
{
	TX += x;
	TY += y;
	TZ += z;
}
// rotate
void Matrix::SetRotation(float x, float y, float z)
{
	R11 = cos(y) * cos(z);
	R12 = -sin(z) * cos(y);
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