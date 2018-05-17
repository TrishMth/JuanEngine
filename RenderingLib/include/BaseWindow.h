#pragma once
#include "GlobalStructs.h"
namespace Rendering {

	class BaseWindow {

	public:
		BaseWindow(const int &ID, const float &posX, const float &posY, const float &width, const float &height);
		~BaseWindow();

		WindowTransform GetTransform() const {
			return wndTrans;
		}

	private:
		WindowTransform wndTrans{ 0 };

		int m_ID;
	};
}