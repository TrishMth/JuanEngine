#include "..\include\D2D1Rendering.h"

Rendering::D2D1Rendering::D2D1Rendering()
	:m_pD2DFactory(nullptr), m_pRenderTarget(nullptr)
{
	m_baseWnd = new BaseWindow(0, 50, 50, 100, 100);
	m_wndTrans = m_baseWnd->GetTransform();
	m_pWndHandler = new WindowHandler();
	m_pWndHandler->AddToCurrentWindows(m_baseWnd);
}

Rendering::D2D1Rendering::D2D1Rendering(const D2D1Rendering &)
{
}

Rendering::D2D1Rendering::~D2D1Rendering()
{
}

void Rendering::D2D1Rendering::CreateRenderTarget(const HWND & hWnd)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	RECT rect;
	GetClientRect(hWnd, &rect);

	m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(
				rect.right - rect.left,
				rect.bottom - rect.top)
		),
		&m_pRenderTarget);
	if (!m_pRenderTarget)
	{
		return;
	}
}

void Rendering::D2D1Rendering::CreateBrush(D2D1::ColorF color)
{
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_pBrush);
}

void Rendering::D2D1Rendering::RenderWindow(const WindowHandler* wndHandler)
{
	WindowTransform wndTrans = wndHandler->m_activeWnd->GetTransform();

	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->FillRectangle(
		D2D1::RectF(
			wndTrans.X,
			wndTrans.Y,
			wndTrans.X + wndTrans.Width,
			wndTrans.Y + wndTrans.Height),
		m_pBrush
	);

	//m_pRenderTarget->FillRectangle(
	//	D2D1::RectF(
	//		m_wndTrans.X,
	//		m_wndTrans.Y,
	//		m_wndTrans.X + m_wndTrans.Width,
	//		m_wndTrans.Y + m_wndTrans.Height),
	//	m_pBrush
	//);

	m_pRenderTarget->EndDraw();
}
