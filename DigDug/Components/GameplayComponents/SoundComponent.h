#pragma once
#include "Component.h"

namespace dae
{
	class SoundComponent final : public Component
	{
	public:
		SoundComponent(const std::string& audioPath, int volume);
		~SoundComponent() = default;
	private:
		unsigned short m_Id;
		int m_Volume;
	};
}


