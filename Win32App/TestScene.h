#ifndef __TESTSCENE_H_
#define __TESTSCENE_H_

#include <Scene\Scene.h>
#include <Scene\Model.h>
#include <Shader\LightShader.h>
#include <Scene\Light.h>
#include <Scene\Camera.h>
#include <Scene\Text.h>
#include <Systems\LogManager.h>

class TestScene : public Engine::Scene
{
private:
	Engine::Camera* m_camera;
	Engine::Model* m_model;
	Engine::Light* m_light;
	//Engine::Text* m_text;

	bool _initialize(void);
public:
	TestScene(void);
	virtual ~TestScene(void);

	void Shutdown(void);
	void Render3D(void);
	void Render2D(void);
	void Update(double dTime){};
};
#endif //__TESTSCENE_H_