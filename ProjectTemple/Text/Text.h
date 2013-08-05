///////////////////////////////////////////////////////////////
// Filename:	Text.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __TEXT_H_
#define __TEXT_H_

#include <Text\Font.h>
#include <Scene\Texture.h>
#include <string>

namespace Engine
{
	class Text
	{
	private:
		Texture* m_builtText;
	public:
		Text(void);
		Text(const Text &other);
		virtual ~Text(void);

		void BuildText(const std::string& text, Font* font);
		void RenderText(void);
	};
}

#endif //__TEXT_H_