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
bool Texture::Initialize(const std::string& fileName)
{
	HRESULT result;

	ID3D11Texture2D* tex;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_TEXTURE2D_DESC desc;
	ID3D11Device* device = Overlord::GetInstance()->GetDevice();

	result = D3DX11CreateTextureFromFile(device, fileName.c_str(), NULL, NULL, (ID3D11Resource**)(&tex), NULL);
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

bool Texture::Initialize(int* data, int width, int height)
{
	HRESULT result;
	
	ID3D11Device* device = Overlord::GetInstance()->GetDevice();

	ID3D11Texture2D* tex;
	D3D11_TEXTURE2D_DESC tdesc;
	D3D11_SUBRESOURCE_DATA tbsd;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	tbsd.pSysMem = (void*)data;
	tbsd.SysMemPitch = width*4;
	tbsd.SysMemSlicePitch = width*height*4;

	tdesc.Width = width;
	tdesc.Height = height;
	tdesc.MipLevels = 1;
	tdesc.ArraySize = 1;

	tdesc.SampleDesc.Count = 1;
	tdesc.SampleDesc.Quality = 0;
	tdesc.Usage = D3D11_USAGE_DEFAULT;
	tdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tdesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	tdesc.CPUAccessFlags = 0;
	tdesc.MiscFlags = 0;

	result = device->CreateTexture2D(&tdesc, &tbsd, &tex);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Texture::Initialize could not create texture from data");
		return false;
	}

	delete[] data;

	tex->GetDesc(&tdesc);
	srvDesc.Format = tdesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = tdesc.MipLevels;

	m_height = tdesc.Height;
	m_width = tdesc.Width;

	result = device->CreateShaderResourceView(tex, NULL, &m_texture);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not create resource view from data (Texture)");
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