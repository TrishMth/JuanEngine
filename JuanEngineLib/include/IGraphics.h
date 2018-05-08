#pragma once

#include <Windows.h>

namespace JE
{
	namespace Mainframework
	{
		class IGraphics
		{
		public:
			IGraphics(const HINSTANCE& hInstance) {};
			virtual bool Init(const HWND& hWnd) = 0;
			virtual void Run() = 0;
			virtual ~IGraphics() {};
		protected:
			HINSTANCE m_hInstance;
		};
	}
}