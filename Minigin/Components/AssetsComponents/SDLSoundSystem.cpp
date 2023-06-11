#include "SDLSoundSystem.h"

#include "ServiceLocator.h"
#include "AudioClip.h"

#include <SDL_mixer.h>
#include <sdl.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "EventHandler.h"

using namespace dae;

class SDLSoundSystem::SoundSystemImpl final
{
public:
	SoundSystemImpl() : m_SoundThread{ &SoundSystemImpl::AudioThread, this }
	{
	}

	~SoundSystemImpl()
	{
		if (m_SoundThread.joinable())
		{
			m_SoundThread.request_stop();
			m_SoundThread.join();
		}
	}

	unsigned short AddSound(const std::string& name, const std::string& path)
	{
		auto it = m_MapSoundId.find(name);
		if (it != m_MapSoundId.end())
		{
			// Sound with the same name already exists, return its ID
			return it->second;
		}

		auto id = static_cast<unsigned short>(m_AudioClips.size());
		m_MapSoundId.emplace(name, id);

		{
			std::lock_guard lock{ m_Mutex };
			m_AudioClips.emplace_back(std::make_unique<AudioClip>(path));
		}

		return id;
	}


	 void Play(unsigned short id, int volume)
	 {
		 {
			 std::lock_guard lock{ m_Mutex };
			 m_SoundQueue.emplace(id, volume);
		 }

		 m_Condition.notify_one();
	 }
	 void Pause()
	 {
		 Mix_Pause(-1);
	 }
	 void Resume()
	 {
		 Mix_Resume(-1);
	 }
	 void Mute()
	 {
		 m_Volume = Mix_Volume(-1, 0);
	 }
	 void Unmute()
	 {
		 if(m_Volume >= 0)
		 {
			 Mix_Volume(-1, m_Volume);
			 m_Volume = -1;
		 }
	 }
	 void SetVolume(float volume)
	 {
		 Mix_Volume(-1, static_cast<int>(MIX_MAX_VOLUME * volume));
	 }
	 //void SetLoop(unsigned short id, bool canLoop);

private:
	enum class SoundState
	{
		PLAY,
		PAUSE,
		RESUME,
		STOP
	};

	struct SoundEvent
	{
		unsigned short id;
		int volume;
	};


	void AudioThread()
	{
		while (true)
		{
			// lock to protect shared data
			std::unique_lock lock{ m_Mutex };

			//wait for notification when the que isn't empty
			m_Condition.wait(lock, [this]() { return !m_SoundQueue.empty(); });

			//get first sound from que
			auto [id, volume] = m_SoundQueue.front();
			m_SoundQueue.pop();

			auto pAudioClip = m_AudioClips[id].get();

			lock.unlock();

			//check if clip is already loaded
			if (!pAudioClip->IsLoaded()) pAudioClip->Load();

			pAudioClip->Play(volume);
		}
	}

	std::jthread m_SoundThread;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;

	std::unordered_map<std::string, unsigned short> m_MapSoundId;
	std::vector<std::unique_ptr<AudioClip>> m_AudioClips;

	std::queue<SoundEvent> m_SoundQueue;

	int m_Volume;
};

dae::SDLSoundSystem::SDLSoundSystem()
{
}

SDLSoundSystem::~SDLSoundSystem()
{
   
}

unsigned short dae::SDLSoundSystem::AddSound(const std::string& name, const std::string& path)
{
	return m_pImplSoundSystem->AddSound(name, path);
}

void dae::SDLSoundSystem::Play(unsigned short id, int volume)
{
	m_pImplSoundSystem->Play(id, volume);
}

void dae::SDLSoundSystem::Pause()
{
	m_pImplSoundSystem->Pause();
}

void dae::SDLSoundSystem::Resume()
{
	m_pImplSoundSystem->Resume();
}

void dae::SDLSoundSystem::Mute()
{
	m_pImplSoundSystem->Mute();
}

void dae::SDLSoundSystem::Unmute()
{
	m_pImplSoundSystem->Unmute();
}

void dae::SDLSoundSystem::SetVolume(float volume)
{
	m_pImplSoundSystem->SetVolume(volume);
}

