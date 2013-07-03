///////////////////////////////////////////////////////////////
// Filename:	Text.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\Text.h>
#include <Systems\LogManager.h>
#include <Systems\Overlord.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Text::Text(void)
{
	m_text = L"";
	m_x = 0.f;
	m_y = 0.f;
	m_size = 32.f;
	m_renderer = NULL;
	m_colour = WHITE;
}

Text::Text(const Text &other)
{
}

Text::~Text(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Text::Initialize(WCHAR* text, float x, float y)
{
	HRESULT result;

	m_text = text;
	m_x = x;
	m_y = y;

	IFW1Factory* factory;
	result = FW1CreateFactory(FW1_VERSION, &factory);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Text::Initialize could not create the font factory");
		return false;
	}

	result = factory->CreateFontWrapper(Overlord::GetInstance()->GetDevice(), L"Arial", &m_renderer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Text::Initialize could not create the font factory");
		return false;
	}

	factory->Release();

	return true;
}

void Text::Render(void)
{
	m_renderer->DrawString(Overlord::GetInstance()->GetDeviceContext(), m_text.c_str(), m_size, m_x, m_y, m_colour, FW1_NOGEOMETRYSHADER);
}

void Text::ChangePosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

float Text::GetXPosition(void)
{
	return m_x;
}

float Text::GetYPosition(void)
{
	return m_y;
}

void Text::SetText(WCHAR* text)
{
	m_text = text;
}

void Text::SetColour(COLOUR_VALUE colour)
{
	m_colour = colour;
}

void Text::SetFontSize(float fontSize)
{
	m_size = fontSize;
}

void Text::Shutdown(void)
{
	if(m_renderer)
	{
		m_renderer->Release();
		m_renderer = NULL;
	}
}