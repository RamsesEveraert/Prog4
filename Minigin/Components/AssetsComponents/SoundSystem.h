#pragma once

#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void Initialize() = 0;
		virtual void Load(const std::string& path) = 0;

		virtual void Play(unsigned short id, float volume) = 0;
		virtual void Pause(unsigned short id) = 0;
		virtual void Resume(unsigned short id) = 0;
		virtual void Stop(unsigned short id) = 0;

		virtual void SetLoop(unsigned short id, bool isLooping) = 0;
	};
}
