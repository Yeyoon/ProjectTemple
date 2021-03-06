///////////////////////////////////////////////////////////////
// Filename:	TextureManager.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_

#include <map>
#include <Systems\Destroyer.h>

namespace Engine
{
	class Texture;

	class TextureManager
	{
		friend class Destroyer<TextureManager>;
	private:
		typedef std::map<std::string, Texture*> MapType;
		MapType m_textureMap;

		static TextureManager* m_instance;
		static Destroyer<TextureManager> m_destroyer;

		TextureManager(void);
		virtual ~TextureManager(void);
	public:
		static TextureManager* GetInstance(void);
		Texture* GetTexture(std::string file);
		Texture* BuildTextureFromData(std::string name, int* data, int width, int height);
	};
}

#endif //__TEXTUREMANAGER_H_