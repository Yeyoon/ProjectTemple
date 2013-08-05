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
#include <Math\Vector2.h>

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
		Vector2 m_dimensions;
		Vector2 m_position;
	public:
		Bitmap(void);
		Bitmap(const Bitmap &other);
		virtual ~Bitmap(void);

		bool Initialize(int width, int height, int x, int y, char* textureFilename);
		void Shutdown(void);
		void Render(void);

		void SetPosition(int posX, int posY);
		void SetPosition(Vector2 pos);
		void Resize(int width, int height);
		void Resize(Vector2 size);
		int GetIndexCount(void);
		Texture* GetTexture(void);
	private:
		bool InitializeBuffers(void);
		void ShutdownBuffers(void);
		bool UpdateBuffers(void);
		void RenderBuffers(void);

		bool LoadTexture(char* filename);
	};
};

#endif //__BITMAP_H_