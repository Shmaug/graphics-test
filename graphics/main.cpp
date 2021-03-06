#include <math.h>
#include <iostream>
#include "graphics.h"
#include "utils.h"
#include <windowsx.h>
#include <debugapi.h>
#include <thread>

#define PI 3.14

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND hwnd;
static HDC hdc;

static int screenWidth = 800;
static int screenHeight = 600;

static int mouseX, mouseY = 0;

int getScreenWidth()
{
	return screenWidth;
}
int getScreenHeight()
{
	return screenHeight;
}
HWND gethwnd()
{
	return hwnd;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const char graphics[]  = "graphics";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = graphics;

    RegisterClass(&wc);

    // Create the window.

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        graphics,                     // Window class
        "Graphics",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

	hdc = GetDC(hwnd);

	init(hdc, hwnd);
	
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	
    ReleaseDC(hwnd, hdc);

    return 1;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
		case WM_DESTROY:
			threadInterrupt = true;
			PostQuitMessage(0);
			return 0;
		case WM_LBUTTONDOWN:
			mouseclick(0, mouseX, mouseY);
			return 0;
		case WM_RBUTTONDOWN:
			mouseclick(1, mouseX, mouseY);
			return 0;
		case WM_LBUTTONUP:
			mouseclick(2, mouseX, mouseY);
			return 0;
		case WM_PAINT:
			
			return 0;
		case WM_RBUTTONUP:
			mouseclick(3, mouseX, mouseY);
			return 0;
		case WM_MOUSEMOVE:
			mouseX = GET_X_LPARAM(lParam);
			mouseY = GET_Y_LPARAM(lParam);
			return 0;
		case WM_SIZE:
			RECT rect;
			GetWindowRect(hwnd, &rect);
			screenWidth = (int)abs(rect.right-rect.left);
			screenHeight = (int)abs(rect.bottom-rect.top);
			return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
