///////////////////////////////////////////////////////////////
// Filename:	Bitmap.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <D3D11.h>

#include <Systems\Overlord.h>
#include <Systems\LogManager.h>
#include <Systems\System.h>
#include <Scene\Bitmap.h>
#include <Scene\TextureManager.h>
#include <Scene\Texture.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Bitmap::Bitmap(void)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}

Bitmap::Bitmap(const Bitmap &other)
{
}

Bitmap::~Bitmap(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Bitmap::Initialize(int width, int height, char* textureFilename)
{
	bool result;

	m_dimensions.x = width;
	m_dimensions.y = height;

	m_position = 0;

	result = InitializeBuffers();
	if(!result)
	{
		LogManager::GetInstance()->Error("Bitmap::Initialize could not initiliaze the bitmap buffers (%s)", textureFilename);
		return false;
	}

	result = LoadTexture(textureFilename);
	if(!result)
	{
		LogManager::GetInstance()->Error("Bitmap::Initialize could not load bitmap texture (%s)", textureFilename);
		false;
	}

	return true;
}

bool Bitmap::Initialize(int width, int height, int* data)
{
	bool result;

	m_position = 0;

	m_dimensions.x = width;
	m_dimensions.y = height;

	result = InitializeBuffers();
	if(!result)
	{
		//LogManager::GetInstance()->Error("Bitmap::Initialize could not initiliaze the bitmap buffers (%s)", textureFilename);
		return false;
	}

	//result = LoadTexture(

	return true;
}

void Bitmap::Shutdown(void)
{
	ShutdownBuffers();
}

void Bitmap::Render(void)
{
	//if((posX != m_prevPosX) || (posY != m_prevPosY))
	//{
		//result = UpdateBuffers(posX, posY);
		//if(!result)
		//{
			//LogManager::GetInstance()->Error("Bitmap::Render could not update the bitmap buffers");
			//return false;
		//}
	//}

	RenderBuffers();
}

int Bitmap::GetIndexCount(void)
{
	return m_indexCount;
}

Texture* Bitmap::GetTexture(void)
{
	return m_texture;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool Bitmap::InitializeBuffers(void)
{
	VertexType* vertices;
	ULONG* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	ID3D11Device* device = Overlord::GetInstance()->GetDevice();

	m_vertexCount = 4;
	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		LogManager::GetInstance()->Error("Bitmap::InitializeBuffers could not create Bitmap Vertex Array");
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		LogManager::GetInstance()->Error("Bitmap::InitializeBuffers could not create Bitmap Index Array");
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	for(i = 0; i<m_indexCount; i++)
		indices[i] = i;

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch  = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Bitmap::InitializeBuffers could not create Bitmap Vertex Buffer");
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Bitmap::InitializeBuffers could not create Bitmap Index Buffer");
		return false;
	}

	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void Bitmap::ShutdownBuffers(void)
{
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool Bitmap::UpdateBuffers(void)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	ID3D11DeviceContext* deviceContext = Overlord::GetInstance()->GetDeviceContext();

	int width =  Overlord::GetInstance()->GetSystem()->GetWindowSize().x;
	int height = Overlord::GetInstance()->GetSystem()->GetWindowSize().y;

	left = (float)((width / 2) * -1) + (float)m_position.x;
	right = left + (float)m_dimensions.x;
	top = (float)(height / 2) - (float)m_position.y;
	bottom = top - (float)m_dimensions.y;

	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		LogManager::GetInstance()->Error("Bitmap::UpdateBuffers could not create the vertex array");
		return false;
	}

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture  = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[1].texture  = D3DXVECTOR2(1.0f, 0.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture  = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[3].texture  = D3DXVECTOR2(1.0f, 1.0f);

	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Bitmap::UpdateBuffers could not map the resource");
		return false;
	}

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	deviceContext->Unmap(m_vertexBuffer, 0);

	delete [] vertices;
	vertices = NULL;

	return true;
}

void Bitmap::RenderBuffers(void)
{
	UINT stride;
	UINT offset;

	ID3D11DeviceContext* deviceContext = Overlord::GetInstance()->GetDeviceContext();

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	return;
}

bool Bitmap::LoadTexture(char* fileName)
{
	/*m_texture = new Texture();
	if(!m_texture)
	{
		LogManager::GetInstance()->Error("Bitmap::LoadTexture could not create texture");
		return false;
	}

	result = m_texture->Initialize(fileName);
	if(!result)
	{
		LogManager::GetInstance()->Error("Bitmap::LoadTexture could not initialize texture");
		return false;
	}*/

	m_texture = TextureManager::GetInstance()->GetTexture(fileName);
	if(!m_texture)
	{
		LogManager::GetInstance()->Error("TextureManager screwed up.");
		return false;
	}

	return true;
}

bool Bitmap::LoadTexture(int* data, std::string name, int width, int height)
{
	m_texture = TextureManager::GetInstance()->BuildTextureFromData(name, data, width, height);
	if(!m_texture)
	{
		LogManager::GetInstance()->Error("TextureManager screwed up.");
		return false;
	}

	return true;
}

void Bitmap::SetPosition(int posX, int posY)
{
	if(m_position.x == posX && m_position.y == posY)
		return;

	m_position = Vector2(posX, posY);
	UpdateBuffers();
}

void Bitmap::SetPosition(Vector2 pos)
{
	if(m_position == pos)
		return;

	m_position = pos;
	UpdateBuffers();
}

void Bitmap::Resize(int width, int height)
{
	if(m_dimensions.x == width && m_dimensions.y == height)
		return;

	m_dimensions = Vector2(width, height);
	UpdateBuffers();
}

void Bitmap::Resize(Vector2 size)
{
	if(m_dimensions == size)
		return;

	m_dimensions = size;
	UpdateBuffers();
}