///////////////////////////////////////////////////////////////
// Filename:	Texture.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\Texture.h>
#include <Systems\Overlord.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Texture::Texture(void)
{
	m_texture = NULL;
}

Texture::Texture(const Texture &other)
{
}

Texture::~Texture(void)
{
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool Texture::Initialize(char* fileName)
{
	HRESULT result;

	ID3D11Texture2D* tex;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_TEXTURE2D_DESC desc;
	ID3D11Device* device = Overlord::GetInstance()->GetDevice();

	result = D3DX11CreateTextureFromFile(device, fileName, NULL, NULL, (ID3D11Resource**)(&tex), NULL);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Texture::Initialize could not load texture (%s)", fileName);
		return false;
	}

	tex->GetDesc(&desc);
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	m_height = desc.Height;
	m_width = desc.Width;

	result = device->CreateShaderResourceView(tex, NULL, &m_texture);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not create resource view (%s)", fileName);
		return false;
	}

	return true;
}

void Texture::Shutdown(void)
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
ID3D11ShaderResourceView* Texture::GetTexture(void)
{
	return m_texture;
}

int Texture::GetHeight(void)
{
	return m_height;
}

int Texture::GetWidth(void)
{
	return m_width;
}