///////////////////////////////////////////////////////////////
// Filename:	ShaderManager.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Shader\ShaderManager.h>

using namespace Engine;

ShaderManager::ShaderManager(void)
{
	m_light = NULL;
	m_texture = NULL;
}

ShaderManager::~ShaderManager(void)
{
	if(m_light)
	{
		m_light->Shutdown();
		delete m_light;
		m_light = NULL;
	}
	if(m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}

void ShaderManager::SetWorldMatrix(D3DXMATRIX world)
{
	m_world = world;
}

void ShaderManager::SetViewMatrix(D3DXMATRIX view)
{
	m_view = view;
}

void ShaderManager::SetProjectionMatrix(D3DXMATRIX proj)
{
	m_proj = proj;
}

void ShaderManager::SetAllMatrices(D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj)
{
	m_world = world;
	m_view = view;
	m_proj = proj;
}

void ShaderManager::SetLight(Light* light)
{
	m_currentLight = light;

	if(m_light != NULL)
	{
		m_light->SetLight(m_currentLight);
	}
}

void ShaderManager::RenderTexture(int index, Texture* texture)
{
	if(m_texture == NULL)
	{
		m_texture = new TextureShader();
		if(m_texture == NULL)
		{
			//break
		}

		if(!(m_texture->Initialize())) 
		{
			//break
		}
	}

	m_texture->SetIndexCount(index);
	if(texture != NULL) m_texture->SetTexture(texture->GetTexture());
	m_texture->Render();
}

void ShaderManager::RenderLight(int index, Texture* diff, Texture* bump, Texture* spec, Texture* alpha)
{
	if(m_light == NULL)
	{
		m_light = new LightShader();
		if(m_light == NULL)
		{
			//break
		}

		if(!(m_light->Initialize())) 
		{
			//break
		}

		m_light->SetLight(m_currentLight);
	}

	m_light->SetIndexCount(index);

	if(diff != NULL) m_light->SetTextureDiff(diff->GetTexture());
	else m_light->SetTextureDiff(NULL);

	if(bump != NULL) m_light->SetTextureBump(bump->GetTexture());
	else m_light->SetTextureBump(NULL);

	if(spec != NULL) m_light->SetTextureSpec(spec->GetTexture());
	else m_light->SetTextureSpec(NULL);

	if(alpha != NULL) m_light->SetTextureAlpha(alpha->GetTexture());
	else m_light->SetTextureAlpha(NULL);

	m_light->Render();
}