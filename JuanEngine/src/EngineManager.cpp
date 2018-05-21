#include "..\include\EngineManager.h"
#include "GlobalStructs.h"
JE::Mainframework::EngineManager* JE::Mainframework::EngineManager::s_pEngineManager = nullptr;

void JE::Mainframework::EngineManager::CreateInstance(const HINSTANCE& hInstance)
{
	if (!s_pEngineManager)
	{
		s_pEngineManager = new EngineManager(hInstance);
		s_pEngineManager->Init();
	}
	// TODO: program already running
}

JE::Mainframework::EngineManager& JE::Mainframework::EngineManager::GetInstance()
{
	return *s_pEngineManager;
}

void JE::Mainframework::EngineManager::ReleaseInstance()
{
	if (s_pEngineManager)
	{
		delete s_pEngineManager;
	}
}

void JE::Mainframework::EngineManager::Init()
{
	m_pWindow = new Window();
	m_MainWndHandle = m_pWindow->WindowInitialize(m_hInstance);
	m_pD2Rendering = new Rendering::D2D1Rendering();
	m_pD2Rendering->CreateRenderTarget(m_MainWndHandle);
	m_pD2Rendering->CreateBrush(D2D1::ColorF::HotPink);

	Rendering::WindowHandler* wndHandler = new Rendering::WindowHandler();

	wndHandler->NewWindow(20, 20, 200, 200);

	m_pD2Rendering->RenderWindow(wndHandler);

}

void JE::Mainframework::EngineManager::Run()
{

	MSG msg{ 0 };

	while (msg.message != WM_QUIT)
	{
		m_pWindow->Run(m_MainWndHandle, msg);
	}
	

}

bool JE::Mainframework::EngineManager::IsInstantiated()
{
	if (!s_pEngineManager)
	{
		return false;
	}
	return true;
}

JE::Mainframework::EngineManager::EngineManager(const HINSTANCE& hInstance)
	:m_hInstance(hInstance)
{
	s_pEngineManager = this;
}

JE::Mainframework::EngineManager::~EngineManager()
{
	s_pEngineManager = nullptr;
}

