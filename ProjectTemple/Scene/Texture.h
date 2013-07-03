///////////////////////////////////////////////////////////////
// Filename:	Texture.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <D3D11.h>
#include <D3DX11tex.h>
#include <Systems\LogManager.h>

namespace Engine
{
	class Texture
	{
		friend class TextureManager;
	private:
		ID3D11ShaderResourceView* m_texture;
		int m_width, m_height;
		Texture(void);
		Texture(const Texture &other);
		virtual ~Texture(void);

		bool Initialize(char* fileName);
		void Shutdown(void);
	public:
		ID3D11ShaderResourceView* GetTexture(void);
		int GetWidth(void);
		int GetHeight(void);
	};
};
#endif //__TEXTURE_H_