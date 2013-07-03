///////////////////////////////////////////////////////////////
// Filename:	Mesh.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\Mesh.h>
#include <Systems\Overlord.h>
#include <Scene\TextureManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Mesh::Mesh(void)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_diffTexture = NULL;
	m_specTexture = NULL;
	m_bumpTexture = NULL;
	m_alphaTexture = NULL;
}

Mesh::Mesh(const Mesh &other)
{
}

Mesh::~Mesh(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Mesh::Initialize(const aiMesh* mesh, aiScene* scene)
{
	ID3D11Device* device = Overlord::GetInstance()->GetDevice();

	//Load all textures possibly, and load the colours necessary.
	{
		aiString szPath;
		const aiMaterial* pcMat = scene->mMaterials[mesh->mMaterialIndex];
		if(AI_SUCCESS == aiGetMaterialString(pcMat, AI_MATKEY_TEXTURE_DIFFUSE(0), &szPath))
		{
			m_diffTexture = TextureManager::GetInstance()->GetTexture(szPath.data);
			if(!m_diffTexture)
			{
				LogManager::GetInstance()->Error("TextureManager screwed up.");
				//return false;
			}
		}
		if(AI_SUCCESS == aiGetMaterialString(pcMat, AI_MATKEY_TEXTURE_HEIGHT(0), &szPath))
		{
			m_bumpTexture = TextureManager::GetInstance()->GetTexture(szPath.data);
			if(!m_bumpTexture)
			{
				LogManager::GetInstance()->Error("TextureManager screwed up.");
				//return false;
			}
		}
		if(AI_SUCCESS == aiGetMaterialString(pcMat, AI_MATKEY_TEXTURE_OPACITY(0), &szPath))
		{
			m_alphaTexture = TextureManager::GetInstance()->GetTexture(szPath.data);
			if(!m_alphaTexture)
			{
				LogManager::GetInstance()->Error("TextureManager screwed up.");
				//return false;
			}
		}
		if(AI_SUCCESS == aiGetMaterialString(pcMat, AI_MATKEY_TEXTURE_SPECULAR(0), &szPath))
		{
			m_specTexture = TextureManager::GetInstance()->GetTexture(szPath.data);
			if(!m_specTexture)
			{
				LogManager::GetInstance()->Error("TextureManager screwed up.");
				//return false;
			}
		}
	}

	//create VBOs
	m_numFaces = mesh->mNumFaces;
	m_vertexCount = mesh->mNumVertices;

	VERTEX* vertices = new VERTEX[m_vertexCount];
	if(!vertices)
	{
		LogManager::GetInstance()->Error("Could not create vertex array");
		return false;
	}

	ULONG* indices = new ULONG[m_numFaces*3];
	if(!indices)
	{
		LogManager::GetInstance()->Error("Could not create index array");
		return false;
	}

	UINT count = 0;

	for(int i = 0; i < m_numFaces; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			indices[count++] = mesh->mFaces[i].mIndices[j];
		}
	}

	float minX=0, minY=0, minZ=0, maxX=0, maxY=0, maxZ=0;

	for(int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].px = mesh->mVertices[i].x;
		vertices[i].py = mesh->mVertices[i].y;
		vertices[i].pz = mesh->mVertices[i].z;

		if(vertices[i].px > maxX) maxX = vertices[i].px;
		else if(vertices[i].px < minX) minX = vertices[i].px;

		if(vertices[i].py > maxY) maxY = vertices[i].py;
		else if(vertices[i].py < minY) minY = vertices[i].py;

		if(vertices[i].pz > maxZ) maxZ = vertices[i].pz;
		else if(vertices[i].pz < minZ) minZ = vertices[i].pz;

		if(mesh->mNormals == NULL)
		{
			vertices[i].nx = vertices[i].ny = vertices[i].nz = 0.0f;
		}
		else
		{
			vertices[i].nx = mesh->mNormals[i].x;
			vertices[i].ny = mesh->mNormals[i].y;
			vertices[i].nz = mesh->mNormals[i].z;
		}

		if(mesh->mTangents == NULL)
		{
			vertices[i].tx = vertices[i].ty = vertices[i].tz = 0.0f;
			vertices[i].bx = vertices[i].by = vertices[i].bz = 0.0f;
		}
		else
		{
			vertices[i].tx = mesh->mTangents[i].x;
			vertices[i].ty = mesh->mTangents[i].y;
			vertices[i].tz = mesh->mTangents[i].z;

			vertices[i].bx = mesh->mBitangents[i].x;
			vertices[i].by = mesh->mBitangents[i].y;
			vertices[i].bz = mesh->mBitangents[i].z;
		}

		if(mesh->HasTextureCoords(0))
		{
			vertices[i].u = mesh->mTextureCoords[0][i].x;
			vertices[i].v = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertices[i].u = vertices[i].v = 0.5f;
		}
	}

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VERTEX) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not create the vertex buffer");
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(ULONG) * m_numFaces * 3;
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
		LogManager::GetInstance()->Error("Could not create the index buffer");
		return false;
	}

	delete [] vertices;
	vertices = NULL;

	delete [] indices;
	indices = NULL;

	//Construct BoundingRect
	m_sizeX = (maxX - minX)/2.0f;
	m_centerX = m_sizeX + minX;

	m_sizeY = (maxY - minY)/2.0f;
	m_centerY = m_sizeY + minY;

	m_sizeZ = (maxZ - minZ)/2.0f;
	m_centerZ = m_sizeZ + minZ;

	return true;
}

void Mesh::Shutdown(void)
{
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}

void Mesh::Render(void)
{
	bool inSight = Overlord::GetInstance()->GetCamera()->GetFrustum()->CheckRectangle(m_centerX, m_centerY, m_centerZ, m_sizeX, m_sizeY, m_sizeZ);

	if(inSight)
	{
		ID3D11DeviceContext* deviceContext = Overlord::GetInstance()->GetDeviceContext();
		UINT stride, offset;

		stride = sizeof(VERTEX);
		offset = 0;

		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Overlord::GetInstance()->GetShaders()->RenderLight((m_numFaces*3), m_diffTexture, m_bumpTexture, m_specTexture, m_alphaTexture);
	}
}

//ID3D11ShaderResourceView* Mesh::GetTexture(void)
//{
//	if(m_diffTexture != NULL)
//		return m_diffTexture->GetTexture();
//	return NULL;
//}
//
//int Mesh::GetIndexCount(void)
//{
//	return (m_numFaces*3);
//}

int Mesh::GetVertexCount(void)
{
	return m_vertexCount;
}

int Mesh::GetFaceCount(void)
{
	return m_numFaces;
}