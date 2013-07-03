///////////////////////////////////////////////////////////////
// Filename:	Scene.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __SCENE_H_
#define __SCENE_H_

//#include <list>
//#include "Model.h"

namespace Engine
{
	class Scene
	{
		//typedef std::list<Model*> VectorType;
	public:
		Scene(void){}
		virtual ~Scene(void){}

		virtual void Render3D(void) = 0;
		virtual void Render2D(void) = 0;
		virtual void Update(double dTime) = 0;

		virtual void Shutdown(void) = 0;
	};
};

#endif //__SCENE_H_