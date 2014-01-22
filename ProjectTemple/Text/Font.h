///////////////////////////////////////////////////////////////
// Filename:	Font.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __FONT_H_
#define __FONT_H_

#include <vector>
#include <string>
#include <map>

namespace Engine
{
	class Texture;

	struct Kerning
	{
		friend class Font;
	private:
		Kerning(void)
		{
			m_second = 0;
			m_amount = 0;
		}

		Kerning(int sec, int amount)
		{
			m_second = sec;
			m_amount = amount;
		}

		int m_second;
		int m_amount;
	};

	struct FontCharacter
	{
		FontCharacter() : m_x(0), m_y(0), m_width(0), m_height(0), 
			m_xOffset(0), m_yOffset(0), m_xAdvance(0), m_page(0),
			m_chnl(0) {}

		int m_x, m_y, m_width, 
			m_height, m_xOffset, m_yOffset, 
			m_xAdvance, m_page, m_chnl;
		std::vector<Kerning> m_kerningList;
	};

	class Font
	{
		friend class FontManager;
		friend class Text;
	private:
		int outlineThickness;
		int fontHeight;
		int base;
		int scaleW, scaleH;
		bool hasOutline;
		std::map<int, FontCharacter*> m_characters;
		std::vector<Texture*> m_pages;

		Font(void);
		Font(const Font& other);
		virtual ~Font(void);

		void ReadFile(const char* fileName);
		int SkipWhiteSpace(std::string &str, int start);
		int FindEndOfToken(std::string &str, int start);

		//Loaders
		void LoadPage(int id, const char* pageFile, const char* fontFile);
		void SetFontInfo(int outlineThickness);
		void SetCommonInfo(int fontHeight, int base, int scaleW, int scaleH, int pages, bool isPacked);
		void AddChar(int id, int x, int y, int w, int h, int xoffset, int yoffset, int xadvance, int page, int chnl);
		void AddKerningPair(int first, int second, int amount);

		//Interpreters
		void InterpretKerning(std::string &str, int start);
		void InterpretChar(std::string &str, int start);
		void InterpretCommon(std::string &str, int start);
		void InterpretInfo(std::string &str, int start);
		void InterpretPage(std::string &str, int start, const char* fontFile);
	};
};
#endif //__FONT_H_