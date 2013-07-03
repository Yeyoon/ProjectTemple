///////////////////////////////////////////////////////////////
// Filename:	DX11System.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __DX11SYSTEM_H_
#define __DX11SYSTEM_H_

#include <Systems\LogManager.h>
#include <DXGI.h>
#include <D3Dcommon.h>
#include <D3D11.h>
#include <D3DX10math.h>

namespace Engine
{
	class DX11System
	{
		friend class Overlord;
	private:
		bool m_vsync;
		int m_videoCardMemory;
		char m_videoCardDesc[128];
		IDXGISwapChain* m_swapChain;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilState* m_depthDisabledStencilState;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11RasterizerState* m_rasterState;
		D3DXMATRIX m_projection;
		D3DXMATRIX m_world;
		D3DXMATRIX m_ortho;
		ID3D11BlendState* m_alphaEnableBlendingState;
		ID3D11BlendState* m_alphaDisableBlendingState;
	public:
		DX11System(void);
		DX11System(const DX11System &other);
		virtual ~DX11System(void);

		bool Initialize(UINT screenWidth, UINT screenHeight, bool vsync, HWND hWnd, bool fullscreen, float zNear, float zFar);
		void Shutdown(void);

		void BeginScene(float red, float green, float blue, float alpha);
		void EndScene(void);

		void TurnZBufferOn(void);
		void TurnZBufferOff(void);

		void TurnAlphaBlendingOn(void);
		void TurnAlphaBlendingOff(void);

		ID3D11Device* GetDevice(void);
		ID3D11DeviceContext* GetDeviceContext(void);

		void GetProjectionMatrix(D3DXMATRIX &proj);
		void GetWorldMatrix(D3DXMATRIX &world);
		void GetOrthoMatrix(D3DXMATRIX &ortho);

		void GetVideoCardInfo(char* cardName, int &memorySize);
	};
};

#endif //__DX11SYSTEM_H_