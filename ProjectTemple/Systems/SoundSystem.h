///////////////////////////////////////////////////////////////
// Filename:	SoundSystem.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __SOUNDSYSTEM_H_
#define __SOUNDSYSTEM_H_

#include <Windows.h>
#include <FMOD\Win32\fmod.hpp>
#include <FMOD\Win32\fmod_errors.h>

#undef PlaySound

namespace Engine
{
	typedef FMOD::Sound Sound;
	typedef FMOD::Channel SoundChannel;

	class SoundSystem
	{
	private:
		FMOD::System* m_system;
		SoundChannel* m_defaultChannel;
	public:
		SoundSystem(void);
		SoundSystem(const SoundSystem &other);
		virtual ~SoundSystem(void);

		bool Initialize(void);
		void Shutdown(void);
		void Update(void);

		void PlaySound(Sound* sound);

		bool CreateSound(char* file, Sound** sound);
		bool CreateStream(char* file, Sound** sound);
	private:
		bool ERRCHECK(FMOD_RESULT res);
	};
};
#endif //__SOUNDSYSTEM_H_