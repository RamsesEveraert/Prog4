#pragma once

#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual unsigned short AddSound(const std::string& name, const std::string& path) = 0;
		virtual void Play(unsigned short id, int volume) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Mute() = 0;
		virtual void Unmute() = 0;

		virtual void SetVolume(float volume) = 0;
		//virtual void SetLoop(unsigned short id, bool isLooping) = 0;
	};
}
