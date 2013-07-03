///////////////////////////////////////////////////////////////
// Filename:	LightShader.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Shader\LightShader.h>
#include <Systems\Overlord.h>
#include <Scene\TextureManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
LightShader::LightShader(void)
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_layout = NULL;
	m_matrixBuffer = NULL;
	m_sampleState = NULL;
	m_lightBuffer = NULL;
	m_cameraBuffer = NULL;

	m_currentTextures[0] = NULL;
	m_currentTextures[1] = NULL;
	m_currentTextures[2] = NULL;
	m_currentTextures[3] = NULL;

	m_defaultBump = TextureManager::GetInstance()->GetTexture("Default Bump.png");
	m_defaultAlpha = TextureManager::GetInstance()->GetTexture("Default Alpha.png");
	m_defaultSpec = TextureManager::GetInstance()->GetTexture("Default Spec.png");
}

LightShader::LightShader(const LightShader &other)
{
}

LightShader::~LightShader(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool LightShader::Initialize(void)
{
	bool result;

	result = InitializeShader("Light.vs", "Light.ps");
	if(!result)
	{
		LogManager::GetInstance()->Error("LightShader::Initialize could not initialize Texture Shaders");
		return false;
	}

	return true;
}

void LightShader::Shutdown(void)
{
	ShutdownShader();
}

bool LightShader::Render(void)
{
	bool result;

	result = SetShaderPatameters();
	if(!result)
	{
		LogManager::GetInstance()->Error("LightShader::Render could not set the texture shader parameters");
		return false;
	}

	RenderShader();

	return true;
}

void LightShader::SetTextureDiff(ID3D11ShaderResourceView* texture)
{
	m_currentTextures[0] = texture;
}

void LightShader::SetTextureBump(ID3D11ShaderResourceView* texture)
{
	if(texture != NULL)
		m_currentTextures[1] = texture;
	else
		m_currentTextures[1] = m_defaultBump->GetTexture();
}

void LightShader::SetTextureSpec(ID3D11ShaderResourceView* texture)
{
	if(texture != NULL)
		m_currentTextures[2] = texture;
	else
		m_currentTextures[2] = m_defaultSpec->GetTexture();
}

void LightShader::SetTextureAlpha(ID3D11ShaderResourceView* texture)
{
	if(texture != NULL)
		m_currentTextures[3] = texture;
	else
		m_currentTextures[3] = m_defaultAlpha->GetTexture();
}

void LightShader::SetTextures(ID3D11ShaderResourceView* diff, ID3D11ShaderResourceView* bump, ID3D11ShaderResourceView* spec, ID3D11ShaderResourceView* alpha)
{
	m_currentTextures[0] = diff;

	if(bump != NULL)
		m_currentTextures[1] = bump;
	else
		m_currentTextures[1] = m_defaultBump->GetTexture();

	if(spec != NULL)
		m_currentTextures[2] = spec;
	else
		m_currentTextures[2] = m_defaultSpec->GetTexture();

	if(alpha != NULL)
		m_currentTextures[3] = alpha;
	else
		m_currentTextures[3] = m_defaultAlpha->GetTexture();
}

void LightShader::SetLight(Light* light)
{
	m_currentLight.ambientColor = light->GetAmbientColor();
	m_currentLight.diffuseColor = light->GetDiffuseColor();
	m_currentLight.lightDirection = light->GetDirection();
	m_currentLight.specularColor = light->GetSpecularColor();
	m_currentLight.specularPower = light->GetSpecularPower();
}

void LightShader::SetIndexCount(int indexCount)
{
	m_currentIndexCount = indexCount;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool LightShader::InitializeShader(char* vsFilename, char* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[5];
	UINT numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	D3D11_BUFFER_DESC cameraBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	ID3D11Device* device = Overlord::GetInstance()->GetDevice();

	errorMessage = NULL;
	vertexShaderBuffer = NULL;
	pixelShaderBuffer = NULL;

	//Compile vertex shader
	result = D3DX11CompileFromFile(	vsFilename, NULL, NULL, "LightVertexShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
									0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			LogManager::GetInstance()->Trace("[HLSL] %s", (char*)errorMessage->GetBufferPointer());
		}
		else
		{
			LogManager::GetInstance()->Warning("LightShader::InitializeShader missing shader file (%s)", vsFilename);
		}
		return false;
	}

	//Compile pixel shader
	result = D3DX11CompileFromFile(	psFilename, NULL, NULL, "LightPixelShader", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 
									0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			LogManager::GetInstance()->Trace("[HLSL] %s", (char*)errorMessage->GetBufferPointer());
		}
		else
		{
			LogManager::GetInstance()->Warning("LightShader::InitializeShader missing shader file (%s)", psFilename);
		}
		return false;
	}

	//Create the vertex and pixel shaders
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create vertex shader");
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create pixel shader");
		return false;
	}

	//Setup the layout of the shader data
	//This NEEDS to match the data in the shader
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TANGENT";
	polygonLayout[3].SemanticIndex = 0;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[3].InputSlot = 0;
	polygonLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[3].InstanceDataStepRate = 0;

	polygonLayout[4].SemanticName = "BINORMAL";
	polygonLayout[4].SemanticIndex = 0;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[4].InputSlot = 0;
	polygonLayout[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[4].InstanceDataStepRate = 0;

	//Get a count of the elements in the layout
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//Create the vertex input layout
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create the vertex input layout");
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = NULL;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = NULL;

	//Setup the description of the dynamic matrix constant buffer
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create the matrix buffer");
		return false;
	}

	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&cameraBufferDesc, NULL, &m_cameraBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create the camera buffer");
		return false;
	}

	//Create the texture sampler state
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create the texture sampler state");
		return false;
	}

	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	result =  device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::InitializeShader could not create the light buffer");
		return false;
	}

	return true;
}

void LightShader::ShutdownShader(void)
{
	if(m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = NULL;
	}

	if(m_cameraBuffer)
	{
		m_cameraBuffer->Release();
		m_cameraBuffer = NULL;
	}

	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = NULL;
	}

	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = NULL;
	}

	if(m_layout)
	{
		m_layout->Release();
		m_layout = NULL;
	}

	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = NULL;
	}

	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = NULL;
	}
}

bool LightShader::SetShaderPatameters(void)
{
	ID3D11DeviceContext* deviceContext;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	LightBufferType* dataPtr2;
	CameraBufferType* dataPtr3;
	UINT bufferNumber;

	deviceContext = Overlord::GetInstance()->GetDeviceContext();

	D3DXMATRIX world = Overlord::GetInstance()->GetShaders()->GetWorldMatrix();
	D3DXMATRIX view = Overlord::GetInstance()->GetShaders()->GetViewMatrix();
	D3DXMATRIX proj = Overlord::GetInstance()->GetShaders()->GetProjectionMatrix();

	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&proj, &proj);

	//Lock the constant buffer so it can be written to
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::SetShaderParameters could not lock the matrix buffer");
		return false;
	}

	//Get a pointer to the data
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	//Copy it over
	dataPtr->world = world;
	dataPtr->view = view;
	dataPtr->projection = proj;

	//Unlock the constant buffer
	deviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	result = deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::SetShaderPatameters could not lock the camera buffer");
		return false;
	}

	dataPtr3 = (CameraBufferType*)mappedResource.pData;
	dataPtr3->cameraPosition = Overlord::GetInstance()->GetCamera()->GetPosition();
	dataPtr3->padding = 0.0f;

	deviceContext->Unmap(m_cameraBuffer, 0);

	bufferNumber = 1;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);

	deviceContext->PSSetShaderResources(0, 4, m_currentTextures);

	result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("LightShader::SetShaderPatameters could not lock the light buffer");
		return false;
	}

	dataPtr2 = (LightBufferType*)mappedResource.pData;

	dataPtr2->ambientColor = m_currentLight.ambientColor;
	dataPtr2->diffuseColor = m_currentLight.diffuseColor;
	dataPtr2->lightDirection = m_currentLight.lightDirection;
	dataPtr2->specularColor = m_currentLight.specularColor;
	dataPtr2->specularPower = m_currentLight.specularPower;

	deviceContext->Unmap(m_lightBuffer, 0);

	bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

void LightShader::RenderShader(void)
{
	ID3D11DeviceContext* deviceContext = Overlord::GetInstance()->GetDeviceContext();

	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	deviceContext->DrawIndexed(m_currentIndexCount, 0, 0);
}