///////////////////////////////////////////////////////////////
// Filename:	Light.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __LIGHT_H_
#define __LIGHT_H_

#include <D3DX10math.h>

namespace Engine
{
	class Light
	{
	private:
		D3DXVECTOR4 m_specularColor;
		D3DXVECTOR4 m_ambientColor;
		D3DXVECTOR4 m_diffuseColor;
		D3DXVECTOR3 m_direction;
		float m_specularPower;
	public:
		Light(void);
		Light(const Light &other);
		virtual ~Light(void);

		void SetAmbientColor(float r, float g, float b, float a);
		void SetDiffuseColor(float r, float g, float b, float a);
		void SetSpecularColor(float r, float g, float b, float a);
		void SetSpecularPower(float pow);
		void SetDirection(float x, float y, float z);

		D3DXVECTOR4 GetAmbientColor(void);
		D3DXVECTOR4 GetDiffuseColor(void);
		D3DXVECTOR4 GetSpecularColor(void);
		float GetSpecularPower(void);
		D3DXVECTOR3 GetDirection(void);
	};
};

#endif //__LIGHT_H_