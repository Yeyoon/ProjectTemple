///////////////////////////////////////////////////////////////
// Filename:	FontManager.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __FONTMANAGER_H_
#define __FONTMANAGER_H_

#include <Systems\Destroyer.h>
#include <string>
#include <map>

namespace Engine
{
	class Font;

	class FontManager
	{
		friend class Destroyer<FontManager>;
	private:
		typedef std::map<std::string, Font*> MapType;
		MapType m_fontMap;

		static FontManager* m_instance;
		static Destroyer<FontManager> m_destroyer;

		FontManager(void);
		virtual ~FontManager(void);
	public:
		static FontManager* GetInstance(void);
		//This will be the FONT file, not the texture file.
		Font* GetFont(std::string file);
	};
};

#endif //__FONTMANAGER_H_