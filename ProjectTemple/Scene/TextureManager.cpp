#include <Scene\TextureManager.h>

using namespace Engine;

TextureManager* TextureManager::m_instance = NULL;
Destroyer<TextureManager> TextureManager::m_destroyer;

TextureManager* TextureManager::GetInstance(void)
{
	if(m_instance == NULL)
	{
		m_instance = new TextureManager();
		m_destroyer.setSingleton(m_instance);
	}
	return m_instance;
}

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

Texture* TextureManager::GetTexture(std::string file)
{
	MapType::iterator i = m_textureMap.find(file);
	if(i != m_textureMap.end())
	{
		return (*i).second;
	}

	Texture* texture = new Texture();
	texture->Initialize(const_cast<char*>(file.c_str()));
	m_textureMap[file] = texture;
	return texture;
}