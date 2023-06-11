#pragma once
#include "Component.h"

namespace dae
{
	class SoundComponent final : public Component
	{
	public:
		SoundComponent(const std::string& name, const std::string& path, int volume);
		~SoundComponent() = default;
		unsigned short GetSoundId() const;
		int GetVolume() const;

	private:
		unsigned short m_Id;
		int m_Volume;
	};
}


