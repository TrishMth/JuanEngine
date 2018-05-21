#pragma once
#include "GlobalStructs.h"
namespace Rendering {

	class BaseWindow {

	public:
		BaseWindow(const int &ID, const float &posX, const float &posY, const float &width, const float &height); //TODO Z
		~BaseWindow();

		WindowTransform GetTransform() const {return wndTrans;}

		int SetID() { m_ID++; }
	private:
		WindowTransform wndTrans{ 0 };

		int m_ID;
	};
}