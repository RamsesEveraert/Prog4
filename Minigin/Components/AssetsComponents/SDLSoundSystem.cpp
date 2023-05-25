#include "SDLSoundSystem.h"

#include "ServiceLocator.h"

#include <SDL_mixer.h>
#include <sdl.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "EventQueue.h"

using namespace dae;

dae::SDLSoundSystem::SDLSoundSystem()
	: m_SoundThread{}, m_QueueMutex{}, m_QueueCondition{}, m_SoundQueue{}
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

	// initialization  SDL_Mixer

	if (Mix_Init(MIX_INIT_MP3) != 0)
	{
		std::cout << "Failed to Initialize SDL_Mixer: " << "\n";
		return;
	}

		const int audioBuffers = 4096;

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, audioBuffers) != 0)
	{
		std::cout << "Failed to open audio: " << Mix_GetError() << "\n";
		return;
	}

	EventQueue::GetInstance().AddListener("PlayAudio", [&](const dae::Event& event) { // []scope, () parameters, {} fction body
		
		const unsigned short id = GetSoundDataFromEvent<unsigned short>(event);
		const int volume = GetSoundDataFromEvent<int>(event);
		const bool canLoop = GetSoundDataFromEvent<bool>(event);
		const std::string soundPath = GetSoundDataFromEvent<std::string>(event);

		Play(id, volume, soundPath, canLoop);

	}); 

	EventQueue::GetInstance().AddListener("PauseAudio", [&](const dae::Event& event) {

		unsigned short id = GetSoundDataFromEvent<unsigned short>(event);
		Pause(id);

	});
	EventQueue::GetInstance().AddListener("ResumeAudio", [&](const dae::Event& event) {
		
		unsigned short id = GetSoundDataFromEvent<unsigned short>(event);
		Resume(id);

	});
	EventQueue::GetInstance().AddListener("StopAudio", [&](const dae::Event& event) { 
		
		unsigned short id = GetSoundDataFromEvent<unsigned short>(event);
		Stop(id);

	});
	EventQueue::GetInstance().AddListener("SwitchAudioLoop", [&](const dae::Event& /*event*/) {
	
		// todo: idk if needed yet

	});

	// make sound thread
	m_SoundThread = std::jthread{ [this] { ProcessEventQueue(); } };

}

void SDLSoundSystem::Play(unsigned short id, int volume, const std::string& filePath, bool canLoop)
{
	std::scoped_lock lock{ m_QueueMutex };

	Sound sound{};
	sound.id = id;
	sound.volume = volume;
	sound.canLoop = canLoop;
	sound.audioPath = filePath;
	sound.state = SoundState::PLAY;

	m_SoundQueue.emplace_back(sound);
	m_QueueCondition.notify_one();
}

void SDLSoundSystem::Pause(unsigned short id)
{
	std::scoped_lock lock{ m_QueueMutex };

	Sound sound{};
	sound.id = id;
	sound.state = SoundState::PAUSE;

	m_SoundQueue.emplace_back(sound);
	m_QueueCondition.notify_one();
}

void SDLSoundSystem::Resume(unsigned short id)
{
	std::scoped_lock lock{ m_QueueMutex };

	Sound sound{};
	sound.id = id;
	sound.state = SoundState::RESUME;

	m_SoundQueue.emplace_back(sound);
	m_QueueCondition.notify_one();
}

void SDLSoundSystem::Stop(unsigned short id)
{
	std::scoped_lock lock{ m_QueueMutex };

	Sound sound{};
	sound.id = id;
	sound.state = SoundState::STOP;

	m_SoundQueue.emplace_back(sound);
	m_QueueCondition.notify_one();
}

void SDLSoundSystem::SetLoop(unsigned short id, bool canLoop)
{
	std::scoped_lock lock{ m_QueueMutex };

	// Retrieve the sound that has the same file path
	const auto& soundIt{ std::find_if(begin(m_SoundQueue), end(m_SoundQueue), [&](const Sound& sound) { return sound.id == id; }) };

	soundIt->canLoop = canLoop;
}


void SDLSoundSystem::ProcessEventQueue()
{
	// get stop token

	const std::stop_token& stopToken{ m_SoundThread.get_stop_token() };

	while (!stopToken.stop_requested())
	{
		{
			std::unique_lock<std::mutex> lock(m_QueueMutex);
			m_QueueCondition.wait(lock, [this]() { return !m_SoundQueue.empty(); });
		}

		SoundState soundState{};
		Sound sound{};

		while (!m_SoundQueue.empty())
		{
			// lock queue
			std::scoped_lock lock{ m_QueueMutex };

			// get Sounds to play from queue
			sound = m_SoundQueue.front();
			soundState = sound.state;

			m_SoundQueue.pop_front();
		}

		switch (soundState)
		{
		case dae::SDLSoundSystem::SoundState::PLAY:
			PlaySound(sound);
			break;
		case dae::SDLSoundSystem::SoundState::PAUSE:
			break;
		case dae::SDLSoundSystem::SoundState::RESUME:
			break;
		case dae::SDLSoundSystem::SoundState::STOP:
			break;
		}

	}
}

void SDLSoundSystem::PlaySound(const Sound& sound)
{
	// load sound

	std::stringstream fullAudioPath{};
	fullAudioPath << "../Data/" << sound.audioPath;

	Mix_Chunk* chunk = Mix_LoadWAV(fullAudioPath.str().c_str());

	if (!chunk)
	{
		std::cout << "Error: Sound chunk is null." << std::endl;
		return;
	}

	// Play the sound using SDL_mixer
	const int channel = Mix_PlayChannel(-1, chunk, sound.canLoop ? -1 : 0);
	if (channel == -1)
	{
		std::cout << "Error: Failed to play sound: " << Mix_GetError() << std::endl;
		return;
	}
	Mix_Volume(channel, sound.volume * MIX_MAX_VOLUME);
}