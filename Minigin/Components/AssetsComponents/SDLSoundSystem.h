#pragma once

#include "SoundSystem.h"

#include "EventHandler.h"
#include "Event.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		virtual unsigned short AddSound(const std::string& name, const std::string& path) override;

		virtual void Play(unsigned short id, int volume) override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void Mute() override;
		virtual void Unmute() override;

		virtual void SetVolume(float volume) override;
		//virtual void SetLoop(unsigned short id, bool canLoop) override;


	private:

		class SoundSystemImpl;
		SoundSystemImpl* m_pImplSoundSystem;

	};

}

