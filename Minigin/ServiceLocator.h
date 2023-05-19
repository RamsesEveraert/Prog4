#pragma once
#include <memory>


namespace dae
{
	class ServiceLocator final
	{
	public:
		static AudioSystem& GetAudio();
		template <typename T>
		static void RegisterAudioSystem();
	private:
		static std::unique_ptr<AudioSystem> m_pAudioSystem;
		static std::unique_ptr<DefaultAudioSystem> m_pDefaultAudioSystem;
	};
}
