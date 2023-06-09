#include "ServiceLocator.h"

using namespace dae;

std::unique_ptr<SoundSystem> ServiceLocator::m_pSoundSystemInstance = nullptr;
std::unique_ptr<DefaultSoundSystem> ServiceLocator::m_pDefaultSoundSystemInstance = nullptr;


SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return m_pSoundSystemInstance == nullptr ? *m_pDefaultSoundSystemInstance : *m_pSoundSystemInstance;
}

void dae::ServiceLocator::RegisterAudioSystem(std::unique_ptr<SoundSystem>&& soundsystem)
{
	m_pSoundSystemInstance = (soundsystem == nullptr) ? std::make_unique<DefaultSoundSystem>() : std::move(soundsystem);
}
