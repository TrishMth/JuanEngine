#pragma once
#include <D3D11.h>
#include <d3dx10math.h>
#include <D3Dcompiler.h>

#include "IGraphics.h"
#include "Texture.h"

namespace Rendering {

	class Bitmap {
	public:
		Bitmap();
		Bitmap(const Bitmap&);
		~Bitmap();

		bool Init(ID3D11Device*, int, int, WCHAR*, int, int);
		void Shutdown();
		bool Render(ID3D11DeviceContext*, int, int);

		int GetIndexCount();
		ID3D11ShaderResourceView* GetTexture();

	private:
		struct VertexType 
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		bool InitBuffers(ID3D11Device*);
		void ShutdownBuffers();
		bool UpdateBuffers(ID3D11DeviceContext*, int, int);
		void RenderBuffers(ID3D11DeviceContext*);

		bool LoadTexture(ID3D11Device*, WCHAR*);
		void ReleaseTexture();

		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		int m_vertexCount, m_indexCount;

		int m_screenWidth, m_screenHeight;
		int m_bitmapWidth, m_bitmapHeight;
		int m_previousPosX, m_previousPosY;

	};
}