#include "..\\include\Window.h"
#include "WindowHandler.h"
#include "D2D1Rendering.h"

namespace
{
	JE::Mainframework::Window* g_pWnd = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pWnd->WndProc(hWnd, msg, wParam, lParam);
}

JE::Mainframework::Window::Window()
	: m_pWndHandler(nullptr)
{
	g_pWnd = this;
}

HWND JE::Mainframework::Window::WindowInitialize(HINSTANCE hInstance)
{
	m_pDTest = new Rendering::D2D1Rendering;
	m_pWndHandler = m_pDTest->m_pWndHandler;

	WNDCLASS wndClass{ 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MainWndProc;
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

	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT JE::Mainframework::Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONUP:
		m_pWndHandler->CheckIfInsideWindow(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT: {
			m_pWndHandler->NewWindow(100, 200, 50, 150);
			break;
		};
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


