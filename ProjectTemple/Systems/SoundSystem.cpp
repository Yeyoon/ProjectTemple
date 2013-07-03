///////////////////////////////////////////////////////////////
// Filename:	SoundSystem.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\SoundSystem.h>
#include <Systems\LogManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
SoundSystem::SoundSystem(void)
{
	m_system = 0;
}

SoundSystem::SoundSystem(const SoundSystem &other)
{
}

SoundSystem::~SoundSystem(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool SoundSystem::Initialize(void)
{
	unsigned int version;
	int numDrivers;
	char name[256];
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_system);
	if(!ERRCHECK(result))
	{
		return false;
	}

	result = m_system->getVersion(&version);
	if(!ERRCHECK(result))
	{
		return false;
	}

	if(version < FMOD_VERSION)
	{
		LogManager::GetInstance()->Error("SoundSystem::Initialize an old version of FMOD is present (&08x). This program requires %08x", version, FMOD_VERSION);
		return false;
	}

	result = m_system->getNumDrivers(&numDrivers);
	if(!ERRCHECK(result))
	{
		return false;
	}

	result = m_system->setHardwareChannels(0,0,0,0);
	if(!ERRCHECK(result))
	{
		return false;
	}

	if(numDrivers == 0)
	{
		result = m_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if(!ERRCHECK(result))
		{
			return false;
		}
	}
	else
	{
		result = m_system->getDriverCaps(0, &caps, 0, 0, &speakerMode);
		if(!ERRCHECK(result))
		{
			return false;
		}

		result = m_system->setSpeakerMode(speakerMode);
		if(!ERRCHECK(result))
		{
			return false;
		}

		if(caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			LogManager::GetInstance()->Warning("SoundSystem::Initialize 'Acceleration' slider has been set to off");
			result = m_system->setDSPBufferSize(1024, 10);
			if(!ERRCHECK(result))
			{
				return false;
			}
		}

		result = m_system->getDriverInfo(0, name, 256, 0);
		if(!ERRCHECK(result))
		{
			return false;
		}

		LogManager::GetInstance()->Trace("Sound Driver: %s", name);

		if(strstr(name, "SigmaTel"))
		{
			result = m_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			if(!ERRCHECK(result))
			{
				return false;
			}
		}
	}

	result = m_system->init(100, FMOD_INIT_NORMAL, 0);
	if(result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if(!ERRCHECK(result))
		{
			return false;
		}

		result = m_system->init(100, FMOD_INIT_NORMAL, 0);
		if(result == FMOD_ERR_OUTPUT_CREATEBUFFER)
		{
			result = m_system->setOutput(FMOD_OUTPUTTYPE_WINMM);
			if(!ERRCHECK(result))
			{
				return false;
			}

			result = m_system->init(100, FMOD_INIT_NORMAL, 0);
			if(!ERRCHECK(result))
			{
				return false;
			}
		}
	}
	return true;
}

void SoundSystem::Shutdown(void)
{
	if(m_defaultChannel != NULL) m_defaultChannel->stop();

	if(m_system)
	{
		m_system->release();
		m_system = 0;
	}
}

void SoundSystem::Update(void)
{
	FMOD_RESULT result = m_system->update();
	ERRCHECK(result);
}

void SoundSystem::PlaySound(Sound* sound)
{
	FMOD_RESULT result = m_system->playSound(FMOD_CHANNEL_FREE, sound, false, &m_defaultChannel);
	ERRCHECK(result);
}

bool SoundSystem::CreateSound(char* file, Sound** sound)
{
	FMOD_RESULT result = m_system->createSound(file, FMOD_SOFTWARE, NULL, sound);
	if(!ERRCHECK(result))
	{
		return false;
	}
	return true;
}

bool SoundSystem::CreateStream(char* file, Sound** sound)
{
	FMOD_RESULT result = m_system->createStream(file, FMOD_SOFTWARE, NULL, sound);
	if(!ERRCHECK(result))
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool SoundSystem::ERRCHECK(FMOD_RESULT res)
{
	if(res != FMOD_OK)
	{
		LogManager::GetInstance()->Error("SoundSystem: %d, %s", res, FMOD_ErrorString(res));
		return false;
	}
	return true;
}