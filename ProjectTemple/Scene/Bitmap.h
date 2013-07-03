///////////////////////////////////////////////////////////////
// Filename:	Bitmap.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __BITMAP_H_
#define __BITMAP_H_

#include <D3D11.h>
#include <D3DX10math.h>
#include <Scene\Texture.h>

namespace Engine
{
	class Bitmap
	{
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_indexCount;
		Texture* m_texture;
		int m_screenWidth, m_screenHeight;
		int m_width, m_height;
		int m_prevPosX, m_prevPosY;
	public:
		Bitmap(void);
		Bitmap(const Bitmap &other);
		virtual ~Bitmap(void);

		bool Initialize(int screenWidth, int screenHeight, int width, int height, char* textureFilename);
		void Shutdown(void);
		bool Render(int posX, int posY);

		int GetIndexCount(void);
		Texture* GetTexture(void);
	private:
		bool InitializeBuffers(void);
		void ShutdownBuffers(void);
		bool UpdateBuffers(int posX, int posY);
		void RenderBuffers(void);

		bool LoadTexture(char* filename);
	};
};

#endif //__BITMAP_H_