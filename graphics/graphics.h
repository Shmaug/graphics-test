#include <Windows.h>
#include <thread>

#ifndef dth
#define dth
std::thread drawThread;
bool threadInterrupt;
#endif

#ifndef gdr
#define gdr
void init(HDC hdc, HWND hwnd);
#endif

#ifndef gcl
#define gcl
void mouseclick(int button, int X, int Y);
#endif