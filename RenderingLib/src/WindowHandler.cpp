#include "..\include\WindowHandler.h"

Rendering::WindowHandler::WindowHandler()
	: baseWnd(nullptr)
{
	baseWnd = new BaseWindow(m_ID++, 0, 0, 100, 200);
	
}

Rendering::WindowHandler::~WindowHandler()
{
}

Rendering::BaseWindow* Rendering::WindowHandler::CheckIfInsideWindow(const float & X, const float & Y)
{
	if (X > baseWnd->GetTransform().X && X <  baseWnd->GetTransform().X + baseWnd->GetTransform().Width)
	{
		if (Y >  baseWnd->GetTransform().Y && Y <  baseWnd->GetTransform().Y + baseWnd->GetTransform().Height)
		{
			return baseWnd;
		}
	}
		return nullptr;
}

