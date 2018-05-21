#include "..\include\BaseWindow.h"

Rendering::BaseWindow::BaseWindow(const int & ID, const float & posX, const float & posY, const float & width, const float & height)
{
	wndTrans.X = posX;
	wndTrans.Y = posY;
	wndTrans.Width = width;
	wndTrans.Height = height;
}

Rendering::BaseWindow::~BaseWindow()
{
}