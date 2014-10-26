#include <Windows.h>

#ifndef VERT
#define VERT

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
#endif

#ifndef PI
#define PI 3.14
#endif