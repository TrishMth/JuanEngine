#pragma once
#include "BaseWindow.h"
#include "GlobalStructs.h"
#include <vector>
#include"D2D1Rendering.h"

namespace Rendering {

	class __declspec(dllexport) WindowHandler {

	private:	
		int m_ID;
		std::vector<BaseWindow*> m_allWindows;
		
	public:
		WindowHandler();
		WindowHandler(const WindowHandler&) = delete;
		~WindowHandler();		

		void NewWindow(int x, int y, int width, int height);
		void AddToCurrentWindows(BaseWindow* baseWnd);

		BaseWindow* CheckIfInsideWindow(const float &X, const float &Y);
		//BaseWindow* GetWindow() const {return baseWnd;}
		
		BaseWindow* m_activeWnd;
	};
}