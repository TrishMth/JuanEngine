#include <D3D11.h>
#include <D3Dcompiler.h>
#include "IGraphics.h"
#include <Windows.h>

namespace Rendering {

		class DX11 : public JE::Mainframework::IGraphics
		{
		public:
			bool Init(const HWND& hWnd);
			void Run();
			IGraphics* CreateGraphics(const HINSTANCE& hInstance);
			DX11(const HINSTANCE& hInstance);
			virtual ~DX11();
		

		private:
			IDXGISwapChain* m_pSwapChain;
			ID3D11Device* m_pDevice;
			ID3D11DeviceContext* m_pDeviceCon;
			ID3D11RenderTargetView* m_pBackBuffer;
			ID3D11VertexShader* m_pVertexShader;
			ID3D11InputLayout* m_pInputLayout;
			ID3D11PixelShader* m_pPixelShader;
			ID3D11Buffer* m_pVertexBuffer;			
			FLOAT m_clearRenderColor[4] = { 1,1,1,1 };
			HRESULT CreateDeviceD3D(const HWND& hWnd);
			HRESULT hr;
			void CreateRenderTarget();
			void CleanUpDeviceD3D();
			void InvalidateDeviceObj();
			void CreateDeviceObjects();       
			void InitGraphics();
			bool Failed(HRESULT aResult);

			template<typename T> void SafeRelease(T*& aPointer)
			{
				if (aPointer != nullptr)
				{
					aPointer->Release();
					aPointer = nullptr;
				}
			}
		};	
}