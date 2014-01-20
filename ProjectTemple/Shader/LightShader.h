///////////////////////////////////////////////////////////////
// Filename:	LightShader.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __LIGHTSHADER_H_
#define __LIGHTSHADER_H_

#include <D3D11.h>
#include <D3DX10math.h>

namespace Engine
{
	class Texture;
	class Light;

	class LightShader
	{
		friend class ShaderManager;
		friend class Overlord;
	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

		struct CameraBufferType
		{
			D3DXVECTOR3 cameraPosition;
			float padding;
		};

		struct LightBufferType
		{
			D3DXVECTOR4 ambientColor;
			D3DXVECTOR4 diffuseColor;
			D3DXVECTOR3 lightDirection;
			float specularPower;
			D3DXVECTOR4 specularColor;
		};

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;
		ID3D11Buffer* m_cameraBuffer;
		ID3D11Buffer* m_lightBuffer;
		ID3D11SamplerState* m_sampleState;

		ID3D11ShaderResourceView* m_currentTextures[4];
		Texture *m_defaultBump, *m_defaultSpec, *m_defaultAlpha;
		LightBufferType m_currentLight;
		int m_currentIndexCount;
	//public:
		LightShader(void);
		LightShader(const LightShader &other);
		virtual ~LightShader(void);

		bool Initialize(void);
		void Shutdown(void);
		bool Render(void);

		void SetTextureDiff(ID3D11ShaderResourceView* texture);
		void SetTextureBump(ID3D11ShaderResourceView* texture);
		void SetTextureSpec(ID3D11ShaderResourceView* texture);
		void SetTextureAlpha(ID3D11ShaderResourceView* texture);
		void SetTextures(ID3D11ShaderResourceView* diff, ID3D11ShaderResourceView* bump, ID3D11ShaderResourceView* spec, ID3D11ShaderResourceView* alpha);
		void SetLight(Light* light);
		void SetIndexCount(int indexCount);
	private:
		bool InitializeShader(char* vsFilename, char* psFilename);
		void ShutdownShader(void);
		bool SetShaderPatameters(void);
		void RenderShader(void);
	};
};
#endif //__LIGHTSHADER_H_