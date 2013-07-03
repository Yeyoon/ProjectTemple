///////////////////////////////////////////////////////////////
// Filename:	Model.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __MODEL_H_
#define __MODEL_H_

#include <D3D11.h>
#include <D3DX10math.h>
#include <Systems\LogManager.h>
#include <Scene\Texture.h>
#include <Scene\Mesh.h>
#include <Scene\Light.h>
#include <list>
#include <Math\Vector3.h>
#include <Math\Vector4.h>
//Include Havok
//#include <Systems\Havok.h>

namespace Engine
{
	class Model
	{
		typedef std::list<Mesh*> ListType;
	private:
		ListType m_meshes;
		Vector3 m_position;
		Vector4 m_rotation;
		//hkVector4 m_position;
		//hkVector4 m_rotation;
	public:
		Model(void);
		Model(const Model &other);
		virtual ~Model(void);

		bool Initialize(char* modelFileName);
		void Shutdown(void);
		void Render(void);
		//void Update(double dTime);

		void SetPosition(float x, float y, float z)
		{
			m_position.x = x;
			m_position.y = y;
			m_position.z = z;
		};
		void GetPosition(float* x, float* y, float* z);
	private:
		bool LoadModel(char* modelFileName);
		void ReleaseModel(void);
	};
};
#endif //__MODEL_H_