#pragma once

#include "SoundSystem.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "EventQueue.h"
#include "Event.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem();

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		virtual void Initialize() override;
		virtual void Load(const std::string& path) override;

		virtual void Play(unsigned short id, float volume) override;
		virtual void Pause(unsigned short id) override;
		virtual void Resume(unsigned short id) override;
		virtual void Stop(unsigned short id) override;

		virtual void SetLoop(unsigned short id, bool isLooping) override;

	private:
		struct Sound
		{
			unsigned short id;
			float volume;
			bool canLoop;
		};

		void ProcessEventQueue();
		void PlaySound(const Sound& soundEvent);

		std::jthread m_SoundThread;
		std::mutex m_QueueMutex;
		std::condition_variable m_QueueCondition;
		std::queue<Sound> m_SoundQueue;
	};
}

