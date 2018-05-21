#pragma once
#include "DX11.h"
#include <d2d1.h>
#include "WindowHandler.h" 


namespace Rendering {

	class __declspec(dllexport) D2D1Rendering {

	public:
		D2D1Rendering();
		D2D1Rendering(const D2D1Rendering&);
		~D2D1Rendering();

		void CreateRenderTarget(const HWND& hWnd);
		void CreateBrush(D2D1::ColorF);
		void RenderWindow(const WindowHandler* wndHandler);

		WindowHandler* m_pWndHandler;
	private:

		ID2D1Factory* m_pD2DFactory;
		ID2D1HwndRenderTarget* m_pRenderTarget;

		ID2D1SolidColorBrush* m_pBrush;
		BaseWindow* m_baseWnd;

		WindowTransform m_wndTrans;

	};

}