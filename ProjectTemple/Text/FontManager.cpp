///////////////////////////////////////////////////////////////
// Filename:	FontManager.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Text\FontManager.h>
#include <Text\Font.h>

using namespace Engine;

FontManager* FontManager::m_instance = NULL;
Destroyer<FontManager> FontManager::m_destroyer;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
FontManager::FontManager(void)
{
	m_fontMap.clear();
}

FontManager::~FontManager(void)
{
	for(MapType::iterator i = m_fontMap.begin(); i != m_fontMap.end();)
	{
		delete (*i).second;
		i = m_fontMap.erase(i);
	}
	m_fontMap.clear();
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
FontManager* FontManager::GetInstance(void)
{
	if(m_instance == NULL)
	{
		m_instance = new FontManager();
		m_destroyer.setSingleton(m_instance);
	}
	return m_instance;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
Font* FontManager::GetFont(std::string file)
{
	MapType::iterator i = m_fontMap.find(file);
	if(i != m_fontMap.end())
	{
		return (*i).second;
	}

	Font* font = new Font();
	font->ReadFile(const_cast<char*>(file.c_str()));
	m_fontMap[file] = font;
	return font;
}