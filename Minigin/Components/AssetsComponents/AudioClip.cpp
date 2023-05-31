#include "AudioClip.h"

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace dae;

class AudioClip::AudioClipImpl final
{
public:

	AudioClipImpl(std::string_view path) : m_AudioPath{ path }
	{

	}

	~AudioClipImpl()
	{
		if (m_pChunk)
		{
			Mix_FreeChunk(m_pChunk);
			m_pChunk = nullptr;
		}
	}

	void Load()
	{
		if (!m_pChunk)
		{
			m_pChunk = Mix_LoadWAV(m_AudioPath.c_str());
			if (!m_pChunk)
			{
				std::cout << "Couldn't load '" << m_AudioPath << "'\n";
			}
		}
	}
	void Play(int volume)
	{
		if (m_pChunk)
		{
			Mix_VolumeChunk(m_pChunk, static_cast<int>(MIX_MAX_VOLUME * volume));
			int channel = Mix_PlayChannel(-1, m_pChunk, 0);

			if (channel == -1)
			{
				std::cout << "No free channel to play: " << m_AudioPath << "\n";
			}
		}
	}
	bool IsLoaded() const
	{
		return (m_pChunk) ? true : false;
	}
	
private:
	std::string m_AudioPath;
	Mix_Chunk* m_pChunk{};

};

AudioClip::AudioClip(std::string_view filepath)
{
	m_AudioClipImpl = new AudioClipImpl(filepath);
}

void AudioClip::Load()
{
	m_AudioClipImpl->Load();
}

void AudioClip::Play(int volume)
{
	m_AudioClipImpl->Play(volume);
}

bool AudioClip::IsLoaded() const
{
	return m_AudioClipImpl->IsLoaded();
}

AudioClip::~AudioClip()
{
	delete m_AudioClipImpl;
}
