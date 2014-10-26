#include <Windows.h>
#include <thread>

#ifndef gfx
#define gfx
std::thread drawThread;
bool threadInterrupt;

void init(HDC hdc, HWND hwnd);

void mouseclick(int button, int X, int Y);
#endif