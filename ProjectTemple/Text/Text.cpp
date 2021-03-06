///////////////////////////////////////////////////////////////
// Filename:	Text.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Text\Text.h>
#include <Scene\TextureManager.h>
#include <Text\Font.h>
#include <Scene\Bitmap.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Text::Text(void)
{
	m_builtText = NULL;
}

Text::Text(const Text &other)
{
	m_builtText = other.m_builtText;
}

Text::~Text(void)
{
	//TextureManager::GetInstance()->
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
void Text::BuildText(const std::string& name, Font* font)
{
	//m_builtText->Initialize(
}

void Text::RenderText(void)
{
	m_builtText->Render();
}