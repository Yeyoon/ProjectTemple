/////////////////////////////////////////////////////////////////
//// Filename:	Text.cpp
//// Author:		Daniel Cossu
//// Company:		Ripe Tomato Studios
/////////////////////////////////////////////////////////////////
//#include <Scene\Text.h>
//#include <Systems\LogManager.h>
//#include <Systems\Overlord.h>
//
//using namespace Engine;
//
/////////////////////////////////////////////////////////////////
//// Constructors and Destructors
/////////////////////////////////////////////////////////////////
//Text::Text(void)
//{
//	m_text = L"";
//	m_x = 0.f;
//	m_y = 0.f;
//	m_size = 32.f;
//	m_colour = WHITE;
//}
//
//Text::Text(const Text &other)
//{
//}
//
//Text::~Text(void)
//{
//}
//
/////////////////////////////////////////////////////////////////
//// Public Functions
/////////////////////////////////////////////////////////////////
//bool Text::Initialize(WCHAR* text, float x, float y)
//{
//	m_text = text;
//	m_x = x;
//	m_y = y;
//
//	return true;
//}
//
//void Text::Render(void)
//{
//	
//}
//
//void Text::ChangePosition(float x, float y)
//{
//	m_x = x;
//	m_y = y;
//}
//
//float Text::GetXPosition(void)
//{
//	return m_x;
//}
//
//float Text::GetYPosition(void)
//{
//	return m_y;
//}
//
//void Text::SetText(WCHAR* text)
//{
//	m_text = text;
//}
//
//void Text::SetColour(COLOUR_VALUE colour)
//{
//	m_colour = colour;
//}
//
//void Text::SetFontSize(float fontSize)
//{
//	m_size = fontSize;
//}
//
//void Text::Shutdown(void)
//{
//}