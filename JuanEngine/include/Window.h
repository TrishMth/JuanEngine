#include <Windows.h>
#include <windowsx.h>
#include "WindowHandler.h"

namespace JE {

	namespace Mainframework {

		class Window {
		public:
			Window(); 
			HWND WindowInitialize(const HINSTANCE hInstance);
			void Run(const HWND& hWnd, MSG& msg);
			LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		private:
			Rendering::WindowHandler* m_pWndHandler;
		};
	}
}