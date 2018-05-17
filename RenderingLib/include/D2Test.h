#pragma once

#include "DX11.h"
#include <d2d1.h>
#include "WindowHandler.h" 

namespace Rendering {

	class __declspec(dllexport) D2Test {

	public: 
		D2Test();
		D2Test(const D2Test&);
		~D2Test();

		void DoSomething(const HWND& hWnd);

		ID2D1Factory* m_pD2DFactory;
		ID2D1HwndRenderTarget* m_pRenderTarget;
	};

}