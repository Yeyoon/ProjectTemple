///////////////////////////////////////////////////////////////
// Filename:	ColorShader.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Shader\ColorShader.h>
#include <Systems\LogManager.h>
#include <fstream>
#include <D3DX11async.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
ColorShader::ColorShader(void)
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	m_layout = NULL;
	m_matrixBuffer = NULL;
}

ColorShader::ColorShader(const ColorShader &other)
{
}

ColorShader::~ColorShader(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool ColorShader::Initialize(ID3D11Device* device, HWND hWnd)
{
	bool result;

	result = InitializeShader(device, hWnd, "Color.vs", "Color.ps");
	if(!result)
	{
		LogManager::GetInstance()->Error("Could not initialize Color Shaders");
		return false;
	}

	return true;
}

void ColorShader::Shutdown(void)
{
	ShutdownShader();
}

bool ColorShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	bool result;

	result = SetShaderPatameters(deviceContext, world, view, projection);
	if(!result)
	{
		LogManager::GetInstance()->Error("Could not set the color shader parameters");
		return false;
	}

	RenderShader(deviceContext, indexCount);

	return true;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool ColorShader::InitializeShader(ID3D11Device* device, HWND hWnd, char* vsFilename, char* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	UINT numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	errorMessage = NULL;
	vertexShaderBuffer = NULL;
	pixelShaderBuffer = NULL;

	//Compile vertex shader
	result = D3DX11CompileFromFile(	vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 
									0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			LogManager::GetInstance()->Trace("[HLSL] %s", (char*)errorMessage->GetBufferPointer());
		}
		else
		{
			LogManager::GetInstance()->Warning("Missing shader file (%s)", vsFilename);
		}
		return false;
	}

	//Compile pixel shader
	result = D3DX11CompileFromFile(	psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 
									0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			LogManager::GetInstance()->Trace("[HLSL] %s", (char*)errorMessage->GetBufferPointer());
		}
		else
		{
			LogManager::GetInstance()->Warning("Missing shader file (%s)", psFilename);
		}
		return false;
	}

	//Create the vertex and pixel shaders
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not create vertex shader");
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not create pixel shader");
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

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	//Get a count of the elements in the layout
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//Create the vertex input layout
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not create the vertex input layout");
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
		LogManager::GetInstance()->Error("Could not create the matrix buffer");
		return false;
	}

	return true;
}

void ColorShader::ShutdownShader(void)
{
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

bool ColorShader::SetShaderPatameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	UINT bufferNumber;

	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&projection, &projection);

	//Lock the constant buffer so it can be written to
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("Could not lock the matrix buffer");
		return false;
	}

	//Get a pointer to the data
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	//Copy it over
	dataPtr->world = world;
	dataPtr->view = view;
	dataPtr->projection = projection;

	//Unlock the constant buffer
	deviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;
}

void ColorShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	deviceContext->DrawIndexed(indexCount, 0, 0);
}