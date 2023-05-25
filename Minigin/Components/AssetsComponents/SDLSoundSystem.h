#pragma once

#include "SoundSystem.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <List>
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

		virtual void Play(unsigned short id, int volume, const std::string& filePath, bool canLoop = false) override;
		virtual void Pause(unsigned short id) override;
		virtual void Resume(unsigned short id) override;
		virtual void Stop(unsigned short id) override;
		virtual void SetLoop(unsigned short id, bool canLoop) override;


	private:
		enum class SoundState
		{
				PLAY,
				PAUSE,
				RESUME,
				STOP
		};

		
		struct Sound
		{
			unsigned short id{};
			int volume{};
			bool canLoop{};
			SoundState state{};
			std::string audioPath{};
		};

		void ProcessEventQueue();
		void PlaySound(const Sound& soundEvent);

		template<typename T>
		T GetSoundDataFromEvent(const dae::Event& event);
		

		std::jthread m_SoundThread;
		std::mutex m_QueueMutex;
		std::condition_variable m_QueueCondition;
		std::list<Sound> m_SoundQueue;

	};

	template<typename T>
	inline T GetSoundDataFromEvent(const dae::Event& event)
	{
		for (const auto& data : event.data)
		{
			if (data.type() == typeid(T))
			{
				return std::any_cast<T>(data);
			}
		}

		return T{};
	}

}

