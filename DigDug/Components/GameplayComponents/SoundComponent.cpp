#include "SoundComponent.h"
#include "ServiceLocator.h"

using namespace dae;

dae::SoundComponent::SoundComponent(const std::string& name, const std::string& path, int volume)
	: m_Volume{ volume }
{
	auto& soundSystem = ServiceLocator::GetSoundSystem();
	m_Id = soundSystem.AddSound(name, path);
}
