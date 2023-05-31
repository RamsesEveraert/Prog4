#include "ServiceLocator.h"

using namespace dae;

SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return m_pSoundSystemInstance == nullptr ? *m_pDefaultSoundSystemInstance : *m_pSoundSystemInstance;
}

void dae::ServiceLocator::RegisterAudioSystem(std::unique_ptr<SoundSystem>&& soundsystem)
{
	m_pSoundSystemInstance = (soundsystem == nullptr) ? std::make_unique<DefaultSoundSystem>() : std::move(soundsystem);
}
