#include "SDLSoundSystem.h"

#include "ServiceLocator.h"

#include <SDL_mixer.h>
#include <sdl.h>
#include <iostream>

#include "EventQueue.h"

using namespace dae;

dae::SDLSoundSystem::SDLSoundSystem()
{
}

SDLSoundSystem::~SDLSoundSystem()
{
    if (m_SoundThread.joinable())
    {
        m_SoundThread.request_stop();
        m_SoundThread.join();
    }
}

void SDLSoundSystem::Initialize()
{
	int audioRate = 44100;  
	Uint16 audioFormat = AUDIO_S16SYS;
	int audioChannels = 2; 
	int audioBuffers = 4096;

	if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
	{
		std::cout << "Failed to open audio: " << Mix_GetError() << std::endl;
		return;
	}

	EventQueue::GetInstance().AddListener("PlayAudio", [this](const dae::Event& event) {  }); // []scope, () parameters, {} fction body
	EventQueue::GetInstance().AddListener("PauseAudio", [this](const dae::Event& event) { });
	EventQueue::GetInstance().AddListener("ResumeAudio", [this](const dae::Event& event) { });
	EventQueue::GetInstance().AddListener("StopAudio", [this](const dae::Event& event) {  });
	EventQueue::GetInstance().AddListener("SwitchAudioLoop", [this](const dae::Event& event) {  });

}


void dae::SDLSoundSystem::Load(const std::string& path)
{
	//// audio path
	//std::string audioPath{};
	//audioPath = "../Data/" + path;

	//// load audio
	//Mix_Chunk* pSound{ Mix_LoadWAV(audioPath.c_str()) };

	//// Stop if loading the sound failed
	//if (!pSound) return;

	//// Create a sound object from the loaded sdl sound
	//const SDLSound sdlSound{ static_cast<unsigned int>(m_pSounds.size()), pSound, filePath };

	//// Add the newly created sound to the container of sounds
	//m_pSounds.push_back(sdlSound);
}

void SDLSoundSystem::Play(unsigned short id, float volume)
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);
	m_SoundQueue.push({ id, volume });
	m_QueueCondition.notify_one();
}

void SDLSoundSystem::Pause(unsigned short id)
{
	// Pause the sound with the given ID
}

void SDLSoundSystem::Resume(unsigned short id)
{
	// Resume the sound with the given ID
}

void SDLSoundSystem::Stop(unsigned short id)
{
	// Stop the sound with the given ID
}

void SDLSoundSystem::SetLoop(unsigned short id, bool isLooping)
{
	// Set looping for the sound with the given ID
}

void SDLSoundSystem::ProcessEventQueue()
{
	// get stop token

	const std::stop_token& stopToken{ m_SoundThread.get_stop_token() };

	while (!stopToken.stop_requested())
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);

		m_QueueCondition.wait(lock, [this]() { return !m_SoundQueue.empty(); });

		while (!m_SoundQueue.empty())
		{
			// lock queue
			std::scoped_lock lock{ m_QueueMutex };

			// get Sounds to play from queue
			const Sound& sound = m_SoundQueue.front();
			PlaySound(sound);

			m_SoundQueue.pop();
		}
	}
}

void SDLSoundSystem::PlaySound(const Sound& sound)
{
	//Mix_Chunk* chunk = sound.id;
	//if (!chunk)
	//{
	//	std::cout << "Error: Sound chunk is null." << std::endl;
	//	return;
	//}

	//// Play the sound using SDL_mixer
	//int channel = Mix_PlayChannel(-1, chunk, sound.volume * MIX_MAX_VOLUME);
	//if (channel == -1)
	//{
	//	std::cout << "Error: Failed to play sound: " << Mix_GetError() << std::endl;
	//	return;
	//}
}