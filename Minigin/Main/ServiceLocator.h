#pragma once
#include "SoundSystem.h"
#include <memory>


namespace dae
{
	class DefaultSoundSystem final : public SoundSystem
	{
		virtual unsigned short AddSound(const std::string& /*name*/, const std::string& /*path*/) override { return 0; };

		virtual void Play(unsigned short /*id*/, int /*volume*/) override {};
		virtual void Pause() override {};
		virtual void Resume() override {};
		virtual void Mute() override {};
		virtual void Unmute() override {};

		virtual void SetVolume(float /*volume*/) override {};
		//virtual void SetLoop(unsigned short /*id*/, bool /*isLooping*/) override {};
	};

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterAudioSystem(std::unique_ptr<SoundSystem>&& soundsystem);
	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
		static std::unique_ptr<DefaultSoundSystem> m_pDefaultSoundSystemInstance;
	};
	
}
