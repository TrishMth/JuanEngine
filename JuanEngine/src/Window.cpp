#include "..\\include\Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		//TODO POPUP before destroy
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND JE::Mainframework::Window::WindowInitialize(HINSTANCE hInstance)
{
	WNDCLASS wndClass{ 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.lpszClassName = "HurensohnClass";

	ATOM atom = 0;
	atom = RegisterClass(&wndClass);
	if (atom == 0)
		return NULL;

	HWND hWnd = CreateWindow(wndClass.lpszClassName, "JuanEngine", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInstance, nullptr);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return hWnd;
}

void JE::Mainframework::Window::Run(const HWND & hWnd, MSG& msg)
{

		//TODO error message;

	if (PeekMessage(&msg,NULL, NULL, NULL,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);		
	}
}


