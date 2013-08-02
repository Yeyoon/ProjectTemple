///////////////////////////////////////////////////////////////
// Filename:	Font.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include "Font.h"
#include "Scene\TextureManager.h"
#include "Systems\LogManager.h"

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Font::Font(void)
{
	outlineThickness = 0;
	fontHeight = 0;
	base = 0;
	scaleW = 0;
	scaleH = 0;
	hasOutline = false;
}

Font::Font(const Font& other)
{
}

Font::~Font(void)
{
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
void Font::ReadFile(const char* fileName)
{
	FILE *f = fopen(fileName, "rb");

	std::string line;

	while(!feof(f))
	{
		line = "";
		line.reserve(256);
		while(feof(f))
		{
			char ch;
			if(fread(&ch, 1, 1, f))
			{
				if(ch != '\n')
					line += ch;
				else 
					break;
			}
		}

		//Skip white spaces
		int pos = SkipWhiteSpace(line, 0);

		//Read token
		int pos2 = FindEndOfToken(line, pos);
		std::string token = line.substr(pos, pos2-pos);

		//Interpret line
		if(token == "info")
			InterpretInfo(line, pos2);
		else if(token == "common")
			InterpretCommon(line, pos2);
		else if(token == "char")
			InterpretChar(line, pos2);
		else if(token == "kerning")
			InterpretKerning(line, pos2);
		else if(token == "page")
			InterpretPage(line, pos2, fileName);
	}

	fclose(f);

	LogManager::GetInstance()->Trace("Font File (%s) loaded!", fileName);
}

int Font::SkipWhiteSpace(std::string &str, int start)
{
	unsigned int n = start;
	while(n < str.size())
	{
		char ch = str[n];
		if( ch != ' ' &&
			ch != '\t' &&
			ch != '\r' &&
			ch != '\n')
			break;

		++n;
	}

	return n;
}

int Font::FindEndOfToken(std::string &str, int start)
{
	unsigned int n = start;
	if(str[n] == '"')
	{
		n++;
		while(n < str.size())
		{
			char ch = str[n];
			if(ch == '"')
			{
				++n;
				break;
			}
			++n;
		}
	}
	else
	{
		while(n < str.size())
		{
			char ch = str[n];
			if( ch == ' ' ||
				ch == '\t' ||
				ch == '\r' ||
				ch == '\n' ||
				ch == '=')
				break;

			++n;
		}
	}

	return n;
}

void Font::LoadPage(int id, const char* pageFile, const char* fontFile)
{
	std::string str;

	//Find that shit!
	str = fontFile;
	for(size_t n = 0; (n = str.find('/', n)) != std::string::npos; )
		str.replace(n, 1, "\\");
	size_t i = str.rfind('\\');
	if(i != std::string::npos)
		str = str.substr(0, i+1);
	else
		str = "";

	//Load it.
	str += pageFile;

	m_pages[id] = TextureManager::GetInstance()->GetTexture(str);
}

void Font::SetFontInfo(int outlineThickness)
{
	this->outlineThickness = outlineThickness;
}

void Font::SetCommonInfo(int fontHeight, int base, int scaleW, int scaleH, int pages, bool isPacked)
{
	this->fontHeight = fontHeight;
	this->base = base;
	this->scaleW = scaleW;
	this->scaleH = scaleH;
	this->m_pages.resize(pages);
	for(int n = 0; n < pages; n++)
		this->m_pages[n] = NULL;

	if(isPacked && this->outlineThickness)
		this->hasOutline = true;
}

void Font::AddChar(int id, int x, int y, int w, int h, int xoffset, int yoffset, int xadvance, int page, int chnl)
{
	//Convert to a 4 element vector
	if     ( chnl == 1 ) chnl = 0x00010000;  // Blue channel
	else if( chnl == 2 ) chnl = 0x00000100;  // Green channel
	else if( chnl == 4 ) chnl = 0x00000001;  // Red channel
	else if( chnl == 8 ) chnl = 0x01000000;  // Alpha channel
	else chnl = 0;

	if(id >= 0)
	{
		FontCharacter* ch = new FontCharacter;
		ch->m_x = x;
		ch->m_y = y;
		ch->m_height = h;
		ch->m_width = w;
		ch->m_xOffset = xoffset;
		ch->m_yOffset = yoffset;
		ch->m_xAdvance = xadvance;
		ch->m_page = page;
		ch->m_chnl = chnl;

		m_characters.insert(std::map<int, FontCharacter*>::value_type(id, ch));
	}
}

void Font::AddKerningPair(int first, int second, int amount)
{
	if(first >= 0 && m_characters[first])
	{
		m_characters[first]->m_kerningList.push_back(Kerning(second, amount));
	}
}

void Font::InterpretKerning(std::string &str, int start)
{
	int first = 0;
	int second = 0;
	int amount = 0;

	int pos, pos2 = start;
	while(true)
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		std::string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if(pos == str.size() || str[pos] != '=') break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		std::string value = str.substr(pos, pos2-pos);

		if(token == "first")
			first = strtol(value.c_str(), 0, 10);
		else if(token == "second")
			second = strtol(value.c_str(), 0, 10);
		else if(token == "amount")
			amount = strtol(value.c_str(), 0, 10);

		if(pos == str.size()) break;
	}

	AddKerningPair(first, second, amount);
}

void Font::InterpretChar(std::string &str, int start)
{
	int id = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int xoffset = 0;
	int yoffset = 0;
	int xadvance = 0;
	int page = 0;
	int chnl = 0;

	int pos, pos2 = start;
	while(true)
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		std::string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if(pos == str.size() || str[pos] != '=') break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		std::string value = str.substr(pos, pos2-pos);

		if(token == "id")
			id = strtol(value.c_str(), 0, 10);
		else if(token == "x")
			x = strtol(value.c_str(), 0, 10);
		else if(token == "y")
			y = strtol(value.c_str(), 0, 10);
		else if(token == "width")
			width = strtol(value.c_str(), 0, 10);
		else if(token == "height")
			height = strtol(value.c_str(), 0, 10);
		else if(token == "xoffset")
			xoffset = strtol(value.c_str(), 0, 10);
		else if(token == "yoffset")
			yoffset = strtol(value.c_str(), 0, 10);
		else if(token == "xadvance")
			xadvance = strtol(value.c_str(), 0, 10);
		else if(token == "page")
			page = strtol(value.c_str(), 0, 10);
		else if(token == "chnl")
			chnl = strtol(value.c_str(), 0, 10);

		if(pos == str.size()) break;
	}

	AddChar(id, x, y, width, height, xoffset, yoffset, xadvance, page, chnl);
}

void Font::InterpretCommon(std::string &str, int start)
{
	int fontHeight;
	int base;
	int scaleW;
	int scaleH;
	int pages;
	int packed;

	int pos, pos2 = start;
	while(true)
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		std::string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if(pos == str.size() || str[pos] != '=') break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		std::string value = str.substr(pos, pos2-pos);

		if(token == "lineHeight")
			fontHeight = (short)strtol(value.c_str(), 0, 10);
		else if(token == "base")
			base = (short)strtol(value.c_str(), 0, 10);
		else if(token == "scaleW")
			scaleW = (short)strtol(value.c_str(), 0, 10);
		else if(token == "scaleH")
			scaleH = (short)strtol(value.c_str(), 0, 10);
		else if(token == "pages")
			pages = strtol(value.c_str(), 0, 10);
		else if(token == "packed")
			packed = strtol(value.c_str(), 0, 10);

		if(pos == str.size()) break;
	}

	SetCommonInfo(fontHeight, base, scaleW, scaleH, pages, packed);
}

void Font::InterpretInfo(std::string &str, int start)
{
	int outlineThickness;

	int pos, pos2 = start;
	while(true)
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		std::string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if(pos == str.size() || str[pos] != '=') break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		std::string value = str.substr(pos, pos2-pos);

		if(token == "outline")
			outlineThickness = (short)strtol(value.c_str(), 0, 10);

		if(pos == str.size()) break;
	}

	SetFontInfo(outlineThickness);
}

void Font::InterpretPage(std::string &str, int start, const char* fontFile)
{
	int id = 0;
	std::string file;

	int pos, pos2 = start;
	while(true)
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		std::string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if(pos == str.size() || str[pos] != '=') break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		std::string value = str.substr(pos, pos2-pos);

		if(token == "id")
			id = strtol(value.c_str(), 0, 10);
		else if(token == "file")
			file = value.substr(1, value.length()-2);

		if(pos == str.size()) break;
	}

	LoadPage(id, file.c_str(), fontFile);
}