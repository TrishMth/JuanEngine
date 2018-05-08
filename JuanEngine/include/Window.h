#include <Windows.h>

namespace JE {

	namespace Mainframework {

		class Window {
		public:
			static HWND WindowInitialize(const HINSTANCE hInstance);
			static void Run(const HWND& hWnd, MSG& msg);

		private:
		};
	}
}