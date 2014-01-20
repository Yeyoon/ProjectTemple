///////////////////////////////////////////////////////////////
// Filename:	Model.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __MODEL_H_
#define __MODEL_H_

#include <list>
#include <Math\Vector3.h>
#include <Math\Vector4.h>

namespace Engine
{
	class Mesh;

	class Model
	{
		typedef std::list<Mesh*> ListType;
	private:
		ListType m_meshes;
		Vector3 m_position;
		Vector4 m_rotation;
	public:
		Model(void);
		Model(const Model &other);
		virtual ~Model(void);

		bool Initialize(char* modelFileName);
		void Shutdown(void);
		void Render(void);
		//void Update(double dTime);

		void SetPosition(float x, float y, float z);
		void GetPosition(float* x, float* y, float* z);
	private:
		bool LoadModel(char* modelFileName);
		void ReleaseModel(void);
	};
};
#endif //__MODEL_H_