#include "SoundComponent.h"
#include "ServiceLocator.h"

using namespace dae;

dae::SoundComponent::SoundComponent(const std::string& audioPath, int volume)
	: m_Volume{ volume }
{
	auto& soundSystem = ServiceLocator::GetSoundSystem();
	m_Id = soundSystem.AddSound(audioPath);
}
