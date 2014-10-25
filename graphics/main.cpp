#include <Windows.h>
#include <math.h>
#include <iostream>
#include "graphics.h"
#include <windowsx.h>

#define PI 3.14

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND hwnd;
static HDC hdc;

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
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

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
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			draw(hdc);
			return 0;
		case WM_LBUTTONDBLCLK:
			mouseclick(0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		case WM_RBUTTONDBLCLK:
			mouseclick(1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
