///////////////////////////////////////////////////////////////
// Filename:	Colour.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __COLOUR_H_
#define __COLOUR_H_

//AaBbGgRr

namespace Engine
{
	//typedef unsigned char BYTE;

	enum COLOUR_VALUE// : UINT32
	{
		WHITE		= 0xffffffff,
		BLACK		= 0xff000000,
		RED			= 0xff0000ff,
		GREEN		= 0xff00ff00,
		BLUE		= 0xffff0000,
		YELLOW		= 0xff00ffff,
		MAGENTA		= 0xffff00ff,
		CYAN		= 0xffffff00
	};

	/*class Colour
	{
	private:
		BYTE m_a, m_b, m_g, m_r;
	public:
		Colour(void);
		Colour(BYTE alpha, BYTE blue, BYTE green, BYTE red);
		Colour(COLOUR_VALUE cv);
		virtual ~Colour(void);
		//BYTE
		BYTE GetRedByte(void);
		BYTE GetBlueByte(void);
		BYTE GetGreenByte(void);
		BYTE GetAlphaByte(void);
		//float
		float GetRedFloat(void);
		float GetBlueFloat(void);
		float GetGreenFloat(void);
		float GetAlphaFloat(void);
		//set
		void SetValues(COLOUR_VALUE cv);
		void SetValues(BYTE alpha, BYTE blue, BYTE green, BYTE red);
	private:
		void HexToABGR(COLOUR_VALUE cv);
	};*/
};

#endif //__COLOUR_H_