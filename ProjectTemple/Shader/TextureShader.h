///////////////////////////////////////////////////////////////
// Filename:	TextureShader.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __TEXTURESHADER_H_
#define __TEXTURESHADER_H_

#include <Systems\LogManager.h>
#include <D3D11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

namespace Engine
{
	class TextureShader
	{
		friend class ShaderManager;
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
		ID3D11SamplerState* m_sampleState;

		ID3D11ShaderResourceView* m_currentTexture;
		int m_currentIndexCount;
	//public:
		TextureShader(void);
		TextureShader(const TextureShader &other);
		virtual ~TextureShader(void);

		bool Initialize(void);
		void Shutdown(void);
		bool Render(void);

		void SetTexture(ID3D11ShaderResourceView* texture);
		void SetIndexCount(int index);
	private:
		bool InitializeShader(char* vsFilename, char* psFilename);
		void ShutdownShader(void);
		bool SetShaderParameters(void);
		void RenderShader(void);
	};
};
#endif //__TEXTURESHADER_H_