#ifndef MATRIX
#define MATRIX
class Matrix
{
public:
	float R11, R12, R13, TX,
		  R21, R22, R23, TY,
		  R31, R32, R33, TZ,
		  SX,  SY,  SZ,  S;
	Matrix();
	void SetPosition(float x, float y, float z);
	void Translate(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void Scale(float x, float y, float z);
};
#endif
