#pragma once
#include <memory>
#include "SoundSystem.h"


namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetAudio();
		template <typename T>
		static void RegisterAudioSystem();
	private:
		static std::unique_ptr<AudioSystem> m_pAudioSystem;
		static std::unique_ptr<DefaultAudioSystem> m_pDefaultAudioSystem;
	};
}
