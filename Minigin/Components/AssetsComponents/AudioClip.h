#pragma once
#include <string>
namespace dae
{
	class AudioClip final
	{
	public:
		AudioClip(std::string filepath);

		void Play(int volume);
		void Load();
		bool IsLoaded() const;
		~AudioClip();

	private:
		class AudioClipImpl;
		AudioClipImpl* m_AudioClipImpl;
	};
}