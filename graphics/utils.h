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
		void setPos(float x,float y,float z);
		Vertex();
		Vertex(float x,float y,float z);
		Vertex(float x,float y,float z,COLORREF color);
	};
}
void box(HDC hdc,int x,int y,int w,int h,COLORREF col);
void line(HDC hdc,int x1,int y1,int x2,int y2,COLORREF col);
#endif

#ifndef PI
#define PI 3.14
#endif