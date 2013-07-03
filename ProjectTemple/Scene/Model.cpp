///////////////////////////////////////////////////////////////
// Filename:	Model.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\Model.h>
#include <assimp\include\assimp.h>
#include <assimp\include\aiPostProcess.h>
#include <assimp\include\aiScene.h>
#include <Systems\Overlord.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Model::Model(void)
{
	m_position = 0;
	m_rotation = 0;
}

Model::Model(const Model &other)
{
}

Model::~Model(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Model::Initialize(char* modelFileName)
{
	bool result;

	result = LoadModel(modelFileName);
	if(!result)
	{
		LogManager::GetInstance()->Error("Model::Initialize could not load the model (%s)", modelFileName);
		return false;
	}

	return true;
}

void Model::Shutdown(void)
{
	for(ListType::iterator i = m_meshes.begin(); i != m_meshes.end();)
	{
		(*i)->Shutdown();
		delete (*i);
		i = m_meshes.erase(i);
	}
	m_meshes.clear();
}

void Model::Render(void)
{
	D3DXMATRIX world, proj, view;
	Overlord::GetInstance()->GetDX11System()->GetWorldMatrix(world);
	Overlord::GetInstance()->GetDX11System()->GetProjectionMatrix(proj);
	Overlord::GetInstance()->GetCamera()->GetViewMatrix(view);
	D3DXMatrixRotationAxis(&world, &D3DXVECTOR3(m_rotation.x, m_rotation.y, m_rotation.z), m_rotation.w);
	D3DXMatrixTranslation(&world, m_position.x, m_position.y, m_position.z);

	Overlord::GetInstance()->GetShaders()->SetAllMatrices(world, view, proj);

	for(ListType::iterator i = m_meshes.begin(); i != m_meshes.end(); i++)
	{
		(*i)->Render();
	}
}

void Model::GetPosition(float* x, float* y, float* z)
{
	(*x) = m_position.x;
	(*y) = m_position.y;
	(*z) = m_position.z;
}

//int Model::GetIndexCount(void)
//{
//	return m_indexCount;
//}

//ID3D11ShaderResourceView* Model::GetTexture(void)
//{
//	return m_texture->GetTexture();
//}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
//bool Model::InitializeBuffers(ID3D11Device* device)
//{
//	VERTEX* vertices;
//	ULONG* indices;
//	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
//	D3D11_SUBRESOURCE_DATA vertexData, indexData;
//	HRESULT result;
//
//	m_vertexCount = 3;
//	m_indexCount = 3;
//
//	vertices = new VERTEX[m_vertexCount];
//	if(!vertices)
//	{
//		LogManager::GetInstance()->Error("Could not create the vertex array");
//		return false;
//	}
//
//	indices = new ULONG[m_indexCount];
//	if(!indices)
//	{
//		LogManager::GetInstance()->Error("Could not create the index array");
//		return false;
//	}
//
//	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); //bottom left
//	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //top middle
//	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);
//
//	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); //bottom right
//	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	indices[0] = 0;
//	indices[1] = 1;
//	indices[2] = 2;
//
//	//set up the description
//	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	vertexBufferDesc.ByteWidth = sizeof(VERTEX) * m_vertexCount;
//	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vertexBufferDesc.CPUAccessFlags = 0;
//	vertexBufferDesc.MiscFlags = 0;
//	vertexBufferDesc.StructureByteStride = 0;
//
//	//give the subresource a pointer to the data
//	vertexData.pSysMem = vertices;
//	vertexData.SysMemPitch = 0;
//	vertexData.SysMemSlicePitch = 0;
//
//	//create it
//	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
//	if(FAILED(result))
//	{
//		LogManager::GetInstance()->Error("Could not create the vertex buffer");
//		return false;
//	}
//
//	//set up the index buffer now
//	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	indexBufferDesc.ByteWidth = sizeof(ULONG) * m_indexCount;
//	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	indexBufferDesc.CPUAccessFlags = 0;
//	indexBufferDesc.MiscFlags = 0;
//	indexBufferDesc.StructureByteStride = 0;
//
//	indexData.pSysMem = indices;
//	indexData.SysMemPitch = 0;
//	indexData.SysMemSlicePitch = 0;
//
//	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
//	if(FAILED(result))
//	{
//		LogManager::GetInstance()->Error("Could not create the index buffer");
//		return false;
//	}
//
//	delete [] vertices;
//	vertices = NULL;
//
//	delete [] indices;
//	indices = NULL;
//
//	return true;
//}

//void Model::ShutdownBuffers(void)
//{
//	if(m_indexBuffer)
//	{
//		m_indexBuffer->Release();
//		m_indexBuffer = NULL;
//	}
//
//	if(m_vertexBuffer)
//	{
//		m_vertexBuffer->Release();
//		m_vertexBuffer = NULL;
//	}
//}

//void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
//{
//	UINT stride, offset;
//
//	stride = sizeof(VERTEX);
//	offset = 0;
//
//	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
//	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//}

//bool Model::LoadTexture(ID3D11Device* device, char* fileName)
//{
//	bool result;
//
//	m_texture = new Texture();
//	if(!m_texture)
//	{
//		LogManager::GetInstance()->Error("Could not create instantiate model texture (%s)", fileName);
//		return false;
//	}
//
//	result = m_texture->Initialize(device, fileName);
//	if(!result)
//	{
//		LogManager::GetInstance()->Error("Could not initialize model texture (%s)", fileName);
//		return false;
//	}
//}

//void Model::ReleaseTexture(void)
//{
	/*if(m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}*/
//}

bool Model::LoadModel(char* modelFileName)
{
	aiScene* scene = (aiScene*)aiImportFile(modelFileName,
		aiProcess_CalcTangentSpace			| //calculate tangents and bitangents, if possible
		aiProcess_JoinIdenticalVertices		| //join identical vertices
		aiProcess_ValidateDataStructure		| //perform a ful validation of the loaders output
		aiProcess_ImproveCacheLocality		| //improve the cache locality of the output vertices
		aiProcess_RemoveRedundantMaterials	| //remove redundant materials
		aiProcess_FindDegenerates			| //remove degenerated polygons from the import
		aiProcess_FindInvalidData			| //detect invalid model data (such as invalid normal vectors and such)
		aiProcess_GenUVCoords				| //convert spherical, cylindrical, box and planar mapping to proper UVs
		aiProcess_TransformUVCoords			| //preprocess UV transformations
		aiProcess_FindInstances				| //search for instanced meshes and remove them by reference to one master
		aiProcess_LimitBoneWeights			| //limit bone weights to 4 per vertex
		aiProcess_OptimizeMeshes			| //if possible, join small meshes
		aiProcess_GenSmoothNormals			| //generate smooth normal vectors
		aiProcess_SplitLargeMeshes			| //split large, unrenderable meshes into submeshes
		aiProcess_Triangulate				| //convert faces to triangles (this is the best feature ever)
		aiProcess_ConvertToLeftHanded		| //make it D3D compatible
		aiProcess_SortByPType				| //make meshes which consist of a single type of primitive
		0);

	if(!scene)
	{
		LogManager::GetInstance()->Error("Model::LoadModel could not load model (into scene) (%s)", modelFileName);
		return false;
	}

	UINT numMeshes = scene->mNumMeshes;

	for(UINT i = 0; i < numMeshes; i++)
	{
		const aiMesh* mesh = scene->mMeshes[i];
		Mesh* tempMesh = new Mesh();
		bool result;
		result = tempMesh->Initialize(mesh, scene);
		if(!result)
			return false;

		m_meshes.push_back(tempMesh);
	}

	return true;
}