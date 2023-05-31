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

		virtual void Play(unsigned short id, int volume) override;

	private:
		std::unique_ptr<SoundSystem> m_RealSoundSystem;

	};

}