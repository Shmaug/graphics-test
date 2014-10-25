#include <Windows.h>

#ifndef GDRAW
#define GDRAW
void draw(HDC hdc);
#endif

#ifndef GMOVE
#define GMOVE
void mouseclick(int button, int X, int Y);
#endif