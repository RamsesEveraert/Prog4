#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem);
		virtual ~LoggingSoundSystem() = default;

		virtual unsigned short AddSound(const std::string& name, const std::string& path) override;

		virtual void Play(unsigned short id, int volume) override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void Mute() override;
		virtual void Unmute() override;

		virtual void SetVolume(float volume) override;

	private:
		std::unique_ptr<SoundSystem> m_RealSoundSystem;

	};

}