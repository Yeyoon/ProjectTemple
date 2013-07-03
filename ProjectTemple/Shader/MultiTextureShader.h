/////////////////////////////////////////////////////////////////
//// Filename:	MultiTextureShader.h
//// Author:		Daniel Cossu
//// Company:		Ripe Tomato Studios
/////////////////////////////////////////////////////////////////
//#ifndef __MULTITEXTURESHADER_H_
//#define __MULTITEXTURESHADER_H_
//
//#include "LogManager.h"
//#include "D3D11.h"
//#include "D3DX10math.h"
//#include "D3DX11async.h"
//#include <fstream>
//using namespace std;
//
//namespace Engine
//{
//	class MultiTextureShader
//	{
//		friend class ShaderManager;
//	private:
//		struct MatrixBufferType
//		{
//			D3DXMATRIX world;
//			D3DXMATRIX view;
//			D3DXMATRIX projection;
//		};
//
//		ID3D11VertexShader* m_vertexShader;
//		ID3D11PixelShader* m_pixelShader;
//		ID3D11InputLayout* m_layout;
//		ID3D11Buffer* m_matrixBuffer;
//		ID3D11SamplerState* m_sampleState;
//
//		ID3D11ShaderResourceView* m_currentTextures[2];
//		int m_currentIndexCount;
//	//public:
//		MultiTextureShader(void);
//		MultiTextureShader(const MultiTextureShader &other);
//		virtual ~MultiTextureShader(void);
//
//		bool Initialize(void);
//		void Shutdown(void);
//		bool Render(void);
//
//		void SetTextures(ID3D11ShaderResourceView** textures);
//		void SetTextures(ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2);
//		void SetIndexCount(int index);
//	private:
//		bool InitializeShader(char* vsFilename, char* psFilename);
//		void ShutdownShader(void);
//		bool SetShaderParameters(void);
//		void RenderShader(void);
//	};
//};
//
//#endif //__MULTITEXTURESHADER_H_