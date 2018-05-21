#include "..\include\WindowHandler.h"

Rendering::WindowHandler::WindowHandler()
{

}

Rendering::WindowHandler::~WindowHandler()
{
}

void Rendering::WindowHandler::NewWindow(int x, int y, int width, int height)
{
	BaseWindow* baseWnd = new BaseWindow(m_ID, x, y, width, height);
	m_ID++;
	m_activeWnd = baseWnd;
	AddToCurrentWindows(baseWnd);
	Rendering::D2D1Rendering* render = new Rendering::D2D1Rendering;
	render->RenderWindow(this);
}

void Rendering::WindowHandler::AddToCurrentWindows(BaseWindow* baseWnd)
{
	m_allWindows.push_back(baseWnd);
}

Rendering::BaseWindow* Rendering::WindowHandler::CheckIfInsideWindow(const float & X, const float & Y)
{
	for (int i = 0; i < m_allWindows.size(); i++)
	{
		if (X > m_allWindows[i]->GetTransform().X && X < m_allWindows[i]->GetTransform().X + m_allWindows[i]->GetTransform().Width)
		{
			if (Y > m_allWindows[i]->GetTransform().Y && Y < m_allWindows[i]->GetTransform().Y + m_allWindows[i]->GetTransform().Height)
			{
				m_activeWnd = m_allWindows[i];
				return m_allWindows[i];
			}
		}
	}
	return nullptr; //no window clicked
}

