///////////////////////////////////////////////////////////////
// Filename:	FontManager.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __FONTMANAGER_H_
#define __FONTMANAGER_H_

#include "Font.h"

namespace Engine
{
	class FontManager
	{
	private:
		static FontManager* m_instance;

		FontManager(void);
		virtual ~FontManager(void);
	};
};

#endif //__FONTMANAGER_H_