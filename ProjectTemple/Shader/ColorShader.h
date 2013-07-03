///////////////////////////////////////////////////////////////
// Filename:	ColorShader.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __COLORSHADER_H_
#define __COLORSHADER_H_

#include <Systems\LogManager.h>
#include <D3D11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

namespace Engine
{
	class ColorShader
	{
	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};
		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;
	public:
		ColorShader(void);
		ColorShader(const ColorShader &other);
		virtual ~ColorShader(void);

		bool Initialize(ID3D11Device* device, HWND hWnd);
		void Shutdown(void);
		bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection);
	private:
		bool InitializeShader(ID3D11Device* device, HWND hWnd, char* vsFilename, char* psFilename);
		void ShutdownShader(void);
		bool SetShaderPatameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection);
		void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
	};
};
#endif //__COLORSHADER_H_