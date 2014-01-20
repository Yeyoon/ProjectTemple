///////////////////////////////////////////////////////////////
// Filename:	Light.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\Light.h>
#include <Systems\LogManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Light::Light(void)
{
}

Light::Light(const Light &other)
{
}

Light::~Light(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
void Light::SetAmbientColor(float r, float g, float b, float a)
{
	m_ambientColor = D3DXVECTOR4(r, g, b, a);
}

void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	m_diffuseColor = D3DXVECTOR4(r, g, b, a);
}

void Light::SetSpecularColor(float r, float g, float b, float a)
{
	m_specularColor = D3DXVECTOR4(r, g, b, a);
}

void Light::SetSpecularPower(float pow)
{
	m_specularPower = pow;
}

void Light::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR4 Light::GetAmbientColor(void)
{
	return m_ambientColor;
}

D3DXVECTOR4 Light::GetDiffuseColor(void)
{
	return m_diffuseColor;
}

D3DXVECTOR4 Light::GetSpecularColor(void)
{
	return m_specularColor;
}

float Light::GetSpecularPower(void)
{
	return m_specularPower;
}

D3DXVECTOR3 Light::GetDirection(void)
{
	return m_direction;
}