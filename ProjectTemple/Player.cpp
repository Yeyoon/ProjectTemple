#include <Systems\Overlord.h>
#include <Scene\Camera.h>
#include <Player.h>

using namespace Engine;

Player::Player(void)
{
	m_camera = NULL;
	m_xRot = m_yRot = 0.f;
	m_xMouseSens = 0.005f;
	m_yMouseSens = 0.008f;

	//m_player = NULL;
	//m_playerBody = NULL;
	//m_playerContext = NULL;
}

Player::~Player(void)
{
}

void Player::Initialize(void)
{
	m_camera = new Camera();

	/*Overlord::GetInstance()->GetHavokWorld()->markForWrite();

	hkVector4 vertA(0,1.f,0);
	hkVector4 vertB(0,-3.f,0);

	hkpCapsuleShape* shape = new hkpCapsuleShape(vertA, vertB, 2.f);

	hkpCharacterRigidBodyCinfo info;
	info.m_mass = 200.f;
	info.m_shape = shape;
	info.m_maxLinearVelocity = 200.f;
	info.m_up.set(m_camera->m_upX, m_camera->m_upY, m_camera->m_upZ);
	info.m_position.set(0.f, 15.f, 0.f);
	info.m_maxSlope = 70.f * HK_REAL_DEG_TO_RAD;

	m_player = new hkpCharacterRigidBody(info);

	shape->removeReference();

	hkpCharacterRigidBodyListener* listener = new hkpCharacterRigidBodyListener();
	m_player->setListener(listener);
	listener->removeReference();

	m_playerBody = m_player->getRigidBody();
	Overlord::GetInstance()->GetHavokWorld()->addEntity(m_player->getRigidBody());

	//Create the state machine
	hkpCharacterState* state;
	hkpCharacterStateManager* manager = new hkpCharacterStateManager();

	state = new hkpCharacterStateOnGround();
	manager->registerState(state, HK_CHARACTER_ON_GROUND);
	state->removeReference();

	state = new hkpCharacterStateInAir();
	manager->registerState(state, HK_CHARACTER_IN_AIR);
	state->removeReference();

	state = new hkpCharacterStateJumping();
	manager->registerState(state, HK_CHARACTER_JUMPING);
	state->removeReference();

	state = new hkpCharacterStateClimbing();
	manager->registerState(state, HK_CHARACTER_CLIMBING);
	state->removeReference();

	state = new hkpCharacterStateFlying();
	manager->registerState(state, HK_CHARACTER_FLYING);
	state->removeReference();

	m_playerContext = new hkpCharacterContext(manager, HK_CHARACTER_FLYING);
	manager->removeReference();

	m_playerContext->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);
	m_playerContext->setFilterEnable(false);

	Overlord::GetInstance()->GetHavokWorld()->unmarkForWrite();*/
}

void Player::Update(double dt)
{
	/*Overlord::GetInstance()->GetHavokWorld()->markForWrite();

	hkpCharacterInput  input;
	hkpCharacterOutput output;
	{
		if(Overlord::GetInstance()->GetInput()->IsKeyHeld(KEY_W))
			input.m_inputUD = -1;
		else if(Overlord::GetInstance()->GetInput()->IsKeyHeld(KEY_S))
			input.m_inputUD = 1;
		else input.m_inputUD = 0;

		if(Overlord::GetInstance()->GetInput()->IsKeyHeld(KEY_A))
			input.m_inputLR = -1;
		else if(Overlord::GetInstance()->GetInput()->IsKeyHeld(KEY_D))
			input.m_inputLR = 1;
		else input.m_inputLR = 0;


	}

	Overlord::GetInstance()->GetHavokWorld()->unmarkForWrite();*/
}