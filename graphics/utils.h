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
		void setPos(float,float,float);
		Vertex();
		Vertex(float,float,float);
		Vertex(float,float,float,COLORREF);
	};
}
#endif

#ifndef PI
#define PI 3.14
#endif