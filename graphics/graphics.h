#include <Windows.h>

#ifndef GDRAW
#define GDRAW
void init(HDC hdc, HWND hwnd);
#endif

#ifndef GCLICK
#define GCLICK
void mouseclick(int button, int X, int Y);
#endif