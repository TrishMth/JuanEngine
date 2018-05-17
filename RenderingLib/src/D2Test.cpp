#include "..\include\D2Test.h"

Rendering::D2Test::D2Test()
	:m_pD2DFactory(nullptr), m_pRenderTarget(nullptr)
{

}

Rendering::D2Test::D2Test(const D2Test &)
{
}

Rendering::D2Test::~D2Test()
{
}

void Rendering::D2Test::DoSomething(const HWND& hWnd)
{
	//Starting point for D2D1 stuff i guess
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	RECT rect;
	GetClientRect(hWnd, &rect);
	
	WindowHandler* wndHandler = new WindowHandler();
	WindowTransform wndTrans = wndHandler->GetWindow()->GetTransform();
	
	m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(
				rect.right - rect.left,
				rect.bottom- rect.top)
		),
		&m_pRenderTarget);
	if (!m_pRenderTarget)
	{
		return;
	}
	ID2D1SolidColorBrush* pBlackBrush;

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::HotPink),
		&pBlackBrush
	);

	m_pRenderTarget->BeginDraw();

	m_pRenderTarget->FillRectangle(
		D2D1::RectF(
		   wndTrans.X,
		wndTrans.Y,
			wndTrans.X + wndTrans.Width,
			wndTrans.Y + wndTrans.Height),
		pBlackBrush
	);

	m_pRenderTarget->EndDraw();	
	
}
