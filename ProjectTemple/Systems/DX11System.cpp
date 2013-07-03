///////////////////////////////////////////////////////////////
// Filename:	DX11System.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\DX11System.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
DX11System::DX11System(void)
{
	m_swapChain = NULL;
	m_device = NULL;
	m_deviceContext = NULL;
	m_renderTargetView = NULL;
	m_depthStencilBuffer = NULL;
	m_depthStencilState = NULL;
	m_depthDisabledStencilState = NULL;
	m_depthStencilView = NULL;
	m_rasterState = NULL;
}

DX11System::DX11System(const DX11System &other)
{
}

DX11System::~DX11System(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool DX11System::Initialize(UINT screenWidth, UINT screenHeight, bool vsync, HWND hWnd, bool fullscreen, float zNear, float zFar)
{
	LogManager::GetInstance()->Trace("DX11System initializing...");

	HRESULT						result;
	IDXGIFactory*				factory;
	IDXGIAdapter*				adapter;
	IDXGIOutput*				adapterOutput;
	UINT						numModes, 
								i, 
								numerator, 
								denominator, 
								stringLength;
	DXGI_MODE_DESC*				displayModeList;
	DXGI_ADAPTER_DESC			adapterDesc;
	int							error;
	DXGI_SWAP_CHAIN_DESC		swapChainDesc;
	D3D_FEATURE_LEVEL			featureLevel;
	ID3D11Texture2D*			backBufferPtr;
	D3D11_TEXTURE2D_DESC		depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC	depthStencilDesc;
	D3D11_DEPTH_STENCIL_DESC	depthDisabledStencilState;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC		rasterDesc;
	D3D11_VIEWPORT				viewport;
	float						fieldOfView, screenAspect;
	D3D11_BLEND_DESC			blendStateDesc;

	m_vsync = vsync;

	//Create a DirectX Graphics Interface (DXGI) factory
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize DXGIFactory could not be created");
		return false;
	}

	//Create an adapter for the primary video card
	result = factory->EnumAdapters(0, &adapter);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the primary display adapter");
		return false;
	}

	//Enumerate the primary adapter output
	result = adapter->EnumOutputs(0, &adapterOutput);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not enumerate the primary adapter outputs");
		return false;
	}

	//Get the number of modes supported in this format
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not get the number of supported display modes");
		return false;
	}

	//Create a list to hold all the possible display modes that fit for this video card / monitor
	displayModeList = new DXGI_MODE_DESC[numModes];
	if(!displayModeList)
	{
		LogManager::GetInstance()->Error("DX11System::Initialize displayModeList could not be initialized");
		return false;
	}

	//fill the list
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not fill the displayModeList");
		return false;
	}

	//Go through every possible mode that fit our window
	//Set the refresh rate accordingly
	for(i = 0; i < numModes; i++)
	{
		if(displayModeList[i].Width == (UINT)screenWidth)
		{
			if(displayModeList[i].Height == (UINT)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	//Get the video card description
	result = adapter->GetDesc(&adapterDesc);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not obtain the video card description");
		return false;
	}

	//Store the dedicated video memory in megabytes
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
	LogManager::GetInstance()->Trace("Available video card memory %d MB", m_videoCardMemory);

	//Convert the name of the video card to a character array and store it
	error = wcstombs_s(&stringLength, m_videoCardDesc, 128, adapterDesc.Description, 128);
	if(error != 0)
	{
		LogManager::GetInstance()->Error("Video card name could not be stored");
		return false;
	}
	LogManager::GetInstance()->Trace("Video Card Name: %s", m_videoCardDesc);

	//Release stuff I don't need
	delete [] displayModeList;
	displayModeList = NULL;

	adapterOutput->Release();
	adapterOutput = NULL;

	adapter->Release();
	adapter = NULL;

	factory->Release();
	factory = NULL;

	//Initialize the swap chain description
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//Set the refresh rate of the back buffer
	if(m_vsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	//Set the usage of the back buffer
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//Set the handle for the window to render to
	swapChainDesc.OutputWindow = hWnd;

	//Turn multisampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Set to full screen or windowed
	swapChainDesc.Windowed = (!fullscreen);

	//Set the scan line ordering and scaling to unspecified
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Discard the back buffer
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	
	//Don't use advanced flags
	swapChainDesc.Flags = 0;

	//Set feature level to DX11
	//Set to 10 to run on laptop.
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	//Default save the settings file to 11.

	//Create the swap chain, Direct3D device, and Direct3D device context
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, 
											&featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, 
											&m_swapChain, &m_device, NULL, &m_deviceContext);

	if(FAILED(result))
	{
		LogManager::GetInstance()->Warning("DX11System::Initalize could not initialize DX11, trying DX10..");

		featureLevel = D3D_FEATURE_LEVEL_10_0;
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, 
											&featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, 
											&m_swapChain, &m_device, NULL, &m_deviceContext);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("DX11System::Initialize could not create SwapChain, Direct3D device and context (10 and 11 fail)");
			return false;
		}

		//Save the Settings variable to 10.
	}

	//Get the pointer to the back buffer
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not obtain the back buffer pointer");
		return false;
	}
	//Create the render target view with the back buffer pointer
	result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the render target view");
		return false;
	}

	backBufferPtr->Release();
	backBufferPtr = NULL;

	//Initialize the description of the depth buffer
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//Set up the description of the depth buffer
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	//Create the depth texture
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the depth texture");
		return false;
	}

	//Initialize the description of the stencil state
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	//Set up the description of the stencil state
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//Stencil operations for front facing pixels
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Stencil operations for back facing pixles
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Create the depth stencil state
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the depth stencil state");
		return false;
	}

	//Setup the second depth stencil for 2D
	ZeroMemory(&depthDisabledStencilState, sizeof(depthDisabledStencilState));

	depthDisabledStencilState.DepthEnable = false; //this is the only difference
	depthDisabledStencilState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilState.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilState.StencilEnable = true;
	depthDisabledStencilState.StencilReadMask = 0xFF;
	depthDisabledStencilState.StencilWriteMask = 0xFF;
	depthDisabledStencilState.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilState.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilState.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilState.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilState.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilState.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilState.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilState.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_device->CreateDepthStencilState(&depthDisabledStencilState, &m_depthDisabledStencilState);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the disabled depth stencil state");
		return false;
	}

	//Set the DSS
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	//Initialize the depth stencil view
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Set it up
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//Create it
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the depth stencil view");
		return false;
	}

	//Bind the render target view and depth stencil buffer to the output render pipeline
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	//Setup the raster decription
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	//Create the rasterizer state
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the rasterizer state");
		return false;
	}

	//Now set it
	m_deviceContext->RSSetState(m_rasterState);

	//Setup the viewport
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	//Create it
	m_deviceContext->RSSetViewports(1, &viewport);

	//Setup projection matrix
	fieldOfView = (float)D3DX_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	//Create the projection matrix
	D3DXMatrixPerspectiveFovLH(&m_projection, fieldOfView, screenAspect, zNear, zFar);

	//Initlialize world matrix
	D3DXMatrixIdentity(&m_world);

	//Create Ortho matrix
	D3DXMatrixOrthoLH(&m_ortho, (float)screenWidth, (float)screenHeight, zNear, zFar);

	//Clear the blend state
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));

	//Create an alpha enabled blend state
	blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
    blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	//Create the blend state
	result = m_device->CreateBlendState(&blendStateDesc, &m_alphaEnableBlendingState);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the enabled blend state");
		return false;
	}
	
	//Change it to disable
	blendStateDesc.RenderTarget[0].BlendEnable = FALSE;

	//Create the disabled state
	result = m_device->CreateBlendState(&blendStateDesc, &m_alphaDisableBlendingState);
	if(FAILED(result))
	{
		LogManager::GetInstance()->Error("DX11System::Initialize could not create the disabled blend state");
		return false;
	}

	LogManager::GetInstance()->Trace("DX11System successfully initialized");

	return true;
}

void DX11System::Shutdown(void)
{
	//Before shutting down set to windowed mode or else an exception wil be thrown in the swap chain
	if(m_swapChain)
		m_swapChain->SetFullscreenState(false, NULL);

	if(m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = NULL;
	}

	if(m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = NULL;
	}

	if(m_depthDisabledStencilState)
	{
		m_depthDisabledStencilState->Release();
		m_depthDisabledStencilState = NULL;
	}

	if(m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = NULL;
	}

	if(m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = NULL;
	}

	if(m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = NULL;
	}

	if(m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = NULL;
	}

	if(m_device)
	{
		m_device->Release();
		m_device = NULL;
	}

	if(m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = NULL;
	}
}

void DX11System::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	//Clear back buffer
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	//Clear depth buffer
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11System::EndScene(void)
{
	if(m_vsync)
		m_swapChain->Present(1, 0);
	else
		m_swapChain->Present(0, 0);
}

void DX11System::TurnZBufferOn(void)
{
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
}

void DX11System::TurnZBufferOff(void)
{
	m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
}

void DX11System::TurnAlphaBlendingOn(void)
{
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};

	m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);
}

void DX11System::TurnAlphaBlendingOff(void)
{
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};

	m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);
}

ID3D11Device* DX11System::GetDevice(void)
{
	return m_device;
}

ID3D11DeviceContext* DX11System::GetDeviceContext(void)
{
	return m_deviceContext;
}

void DX11System::GetProjectionMatrix(D3DXMATRIX &projMat)
{
	projMat = m_projection;
}

void DX11System::GetWorldMatrix(D3DXMATRIX &worldMat)
{
	worldMat = m_world;
}

void DX11System::GetOrthoMatrix(D3DXMATRIX &orthoMat)
{
	orthoMat = m_ortho;
}

void DX11System::GetVideoCardInfo(char* cardName, int &memory)
{
	strcpy_s(cardName, 128, m_videoCardDesc);
	memory = m_videoCardMemory;
}