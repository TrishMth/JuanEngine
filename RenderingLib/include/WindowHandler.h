#pragma once
#include "BaseWindow.h"
#include "GlobalStructs.h"

namespace Rendering {

	class __declspec(dllexport) WindowHandler {

	private:
		WindowTransform wndTrans{0};
		BaseWindow* baseWnd;

		int m_ID;

	public:
		WindowHandler();
		WindowHandler(const WindowHandler&) = delete;
		~WindowHandler();

		BaseWindow* CheckIfInsideWindow(const float &X, const float &Y);

		BaseWindow* GetWindow() const {
			return baseWnd;
		}

	};
}