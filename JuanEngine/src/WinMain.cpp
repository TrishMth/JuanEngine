#include <Windows.h>
#include "..\include\EngineManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpstr, int nCmdShow)
{
	JE::Mainframework::EngineManager::CreateInstance(hInstance);
	if (JE::Mainframework::EngineManager::GetInstance().IsInstantiated())
	{
		JE::Mainframework::EngineManager::GetInstance().Run();
	}
}