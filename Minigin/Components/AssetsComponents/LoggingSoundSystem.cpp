#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
	: m_RealSoundSystem(std::move(soundSystem)) 
{
}

unsigned short dae::LoggingSoundSystem::AddSound(const std::string& name, const std::string& path)
{
	std::cout << "Added sound " << name << " at volume " << path << "\n";
	return m_RealSoundSystem->AddSound(name, path);
}

void dae::LoggingSoundSystem::Play(unsigned short id, int volume)
{
	m_RealSoundSystem->Play(id, volume);
	std::cout << "playing " << id << " at volume " << volume << "\n";
}

void dae::LoggingSoundSystem::Pause()
{
	m_RealSoundSystem->Pause();
	std::cout << "Sound paused \n";
}

void dae::LoggingSoundSystem::Resume()
{
	m_RealSoundSystem->Resume();
	std::cout << "Sound Resumed \n";
}

void dae::LoggingSoundSystem::Mute()
{
	m_RealSoundSystem->Mute();
	std::cout << "Sound muted \n";
}

void dae::LoggingSoundSystem::Unmute()
{
	m_RealSoundSystem->Mute();
	std::cout << "Sound unmuted \n";
}

void dae::LoggingSoundSystem::SetVolume(float volume)
{
	m_RealSoundSystem->SetVolume(volume);
	std::cout << "Set volume to: " << volume << "\n";
}
