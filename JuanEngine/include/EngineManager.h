#pragma once
#include <Windows.h>
#include "IGraphics.h"
#include "Window.h"
#include "D2Test.h"

namespace JE
{
	namespace Mainframework
	{
		typedef IGraphics* (*CREATE_GRAPHICS)(const HINSTANCE& hInstance);
		class EngineManager
		{
		private: 
			static EngineManager* s_pEngineManager;
			IGraphics* m_pGraphics;
			HWND m_MainWndHandle;
			HINSTANCE m_hInstance;
		public:
			static void CreateInstance(const HINSTANCE& hInstance);
			static EngineManager& GetInstance();
			static void ReleaseInstance();

			void Init();
			void Run();
			bool IsInstantiated();

			EngineManager& operator=(const EngineManager&) = delete;
			EngineManager(const EngineManager&) = delete;

			~EngineManager();
		private:
			EngineManager(const HINSTANCE& hInstance);

		};

	}
}