#include "TestScene.h"
#include <Systems\Overlord.h>

TestScene::TestScene(void)
{
	m_camera = NULL;
	m_model = NULL;
	m_light = NULL;
	m_text = NULL;
}

TestScene::~TestScene(void)
{
}

bool TestScene::Initialize(void)
{
	bool result;

	m_camera = new Engine::Camera();
	if(!m_camera)
	{
		Engine::LogManager::GetInstance()->Error("TestScene::Initialize Camera could not be created");
		return false;
	}

	m_camera->SetPosition(100.0f, 400.0f, -10.0f);
	m_camera->SetLookAt(10.0f, 400.0f, -10.0f);

	Engine::Overlord::GetInstance()->SetCamera(m_camera);

	m_model = new Engine::Model();
	if(!m_model)
	{
		Engine::LogManager::GetInstance()->Error("TestScene::Initialize TestModel could not be created");
		return false;
	}

	result = m_model->Initialize("sponza.obj");
	if(!result)
	{
		Engine::LogManager::GetInstance()->Error("TestScene::Initialize TestModel could not be initialized");
		return false;
	}

	m_light = new Engine::Light();
	if(!m_light)
	{
		Engine::LogManager::GetInstance()->Error("TestScene::Initialize Light could not be created");
	}

	m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetDirection(0.0f, -1.0f, 0.0f);
	m_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetSpecularPower(1024.0f);

	m_model->SetPosition(0.0, 0.0, 0.0);

	/*m_bitmap = new Bitmap();
	if(!m_bitmap)
	{
		LogManager::GetInstance()->Error("TestScene::Initialize Bitmap could not be created");
		return false;
	}

	result = m_bitmap->Initialize(screenWidth, screenHeight, 128, 128, "scroll.rtf");
	if(!result)
	{
		LogManager::GetInstance()->Error("TestScene::Initialize Bitmap could not be initialized");
		return false;
	}

	m_textureShader = new TextureShader();
	if(!m_textureShader)
	{
		return false;
	}

	result = m_textureShader->Initialize();
	if(!result)
	{
		return false;
	}*/

	m_text = new Engine::Text();
	if(!m_text)
	{
		Engine::LogManager::GetInstance()->Error("TestScene::Initialize Text could not be created");
		return false;
	}

	result = m_text->Initialize(L"This is a test!", 400.f, 400.f);
	if(!result)
	{
		Engine::LogManager::GetInstance()->Error("TestScene::Initialize Text could not be initialized");
		return false;
	}

	m_text->SetColour(Engine::BLUE);

	Engine::Overlord::GetInstance()->GetShaders()->SetLight(m_light);

	return true;
}

void TestScene::Render3D(void)
{
	//Temporary
	if(Engine::Overlord::GetInstance()->GetInput()->IsKeyDown(Engine::KEY_ESC))
	{
		exit(0);
	}

	Engine::Overlord::GetInstance()->GetCamera()->Render();
	m_model->Render();
}

void TestScene::Render2D(void)
{
	m_text->Render();
}

void TestScene::Shutdown(void)
{
	if(m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}

	if(m_model != NULL)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = NULL;
	}

	if(m_light != NULL)
	{
		delete m_light;
		m_light = NULL;
	}
}