#pragma once
#include "SoundSystem.h"
#include <memory>


namespace dae
{
	class DefaultSoundSystem final : public SoundSystem
	{
		virtual void Initialize() override {};
		virtual void Load(const std::string& path) override {};

		virtual void Play(unsigned short id, float volume) override {};
		virtual void Pause(unsigned short id) override {};
		virtual void Resume(unsigned short id) override {};
		virtual void Stop(unsigned short id) override{};

		virtual void SetLoop(unsigned short id, bool isLooping) override {};
	};


	class ServiceLocator final
	{
	public:
		static SoundSystem& GetAudio();
		static void RegisterAudioSystem(std::unique_ptr<SoundSystem>&& soundsystem);
	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
		static std::unique_ptr<DefaultSoundSystem> m_pDefaultSoundSystemInstance;
	};
	
}
