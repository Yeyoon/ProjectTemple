///////////////////////////////////////////////////////////////
// Filename:	TextureManager.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\TextureManager.h>
#include <Scene\Texture.h>

using namespace Engine;

TextureManager* TextureManager::m_instance = NULL;
Destroyer<TextureManager> TextureManager::m_destroyer;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
TextureManager::TextureManager(void)
{
	m_textureMap.clear();

	Texture* texture = new Texture();
	texture->Initialize("scroll.rtf");
	m_textureMap["scroll.rtf"] = texture;
}

TextureManager::~TextureManager(void)
{
	for(MapType::iterator i = m_textureMap.begin(); i != m_textureMap.end();)
	{
		delete (*i).second;
		i = m_textureMap.erase(i);
	}
	m_textureMap.clear();
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
TextureManager* TextureManager::GetInstance(void)
{
	if(m_instance == NULL)
	{
		m_instance = new TextureManager();
		m_destroyer.setSingleton(m_instance);
	}
	return m_instance;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
Texture* TextureManager::GetTexture(std::string file)
{
	MapType::iterator i = m_textureMap.find(file);
	if(i != m_textureMap.end())
	{
		return (*i).second;
	}

	Texture* texture = new Texture();
	texture->Initialize(file);
	m_textureMap[file] = texture;
	return texture;
}

Texture* TextureManager::BuildTextureFromData(std::string name, int* data, int width, int height)
{
	MapType::iterator i = m_textureMap.find(name);
	if(i != m_textureMap.end())
	{
		return (*i).second;
	}

	Texture* texture = new Texture();
	texture->Initialize(data, width, height);
	m_textureMap[name] = texture;
	return texture;
}