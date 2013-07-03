///////////////////////////////////////////////////////////////
// Filename:	Renderable.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __RENDERABLE_H_
#define __RENDERABLE_H_

namespace Engine
{
	class Renderable
	{
	protected:
		bool bToDie
	public:
		virtual void Render(void) = 0;
		virtual void Update(double dTime) = 0;
		void setToDie(void){bToDie = true;}
		Renderable(void){bToDie = false;}
		virtual ~Renderable(void){}
	};
}

#endif //__RENDERABLE_H_