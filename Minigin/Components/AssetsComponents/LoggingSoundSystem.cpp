#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
	: m_RealSoundSystem(std::move(soundSystem)) 
{
}

void dae::LoggingSoundSystem::Play(unsigned short id, int volume, const std::string& soundPath, bool canLoop)
{
	m_RealSoundSystem->Play(id, volume, soundPath, canLoop);
	std::cout << "playing " << id << " at volume " << volume << "\n";
}
