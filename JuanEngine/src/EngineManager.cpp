#include "..\include\EngineManager.h"
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

}

void JE::Mainframework::EngineManager::Run()
{
	//HMODULE graphicsMod = LoadLibrary("RenderingLib\\RenderingLib.dll");
	//CREATE_GRAPHICS createGraphics = (CREATE_GRAPHICS)GetProcAddress(graphicsMod, "CreateGraphics");
	//m_pGraphics = createGraphics(m_hInstance);
	//m_pGraphics->Init(m_MainWndHandle);

	Rendering::D2Test* fuckyou = new Rendering::D2Test();


	MSG msg{ 0 };

	while (msg.message != WM_QUIT)
	{
		m_pWindow->Run(m_MainWndHandle, msg);
		fuckyou->DoSomething(m_MainWndHandle);
		//m_pGraphics->Run();		
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

