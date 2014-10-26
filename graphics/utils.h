#include <Windows.h>

#ifndef UTIL
#define UTIL
namespace utils
{
	class Vertex
	{
	public:
		COLORREF color;
		float X, Y, Z;
		bool initialized;
		void setPos(float x,float y,float z);
		Vertex();
		Vertex(float x,float y,float z);
		Vertex(float x,float y,float z,COLORREF color);
	};
}
bool pointInTriangle(int x, int y, utils::Vertex p1, utils::Vertex p2, utils::Vertex p3, _Inout_ float alpha, _Inout_ float beta, _Inout_ float gamma);
void box(HDC hdc,int x,int y,int w,int h,COLORREF col);
void line(HDC hdc,utils::Vertex v1, utils::Vertex v2);

#define PI 3.14
#endif