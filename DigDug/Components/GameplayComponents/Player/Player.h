#pragma once
#include "Component.h"

namespace dae
{
	class Player final : public Component
	{
	public:
		Player() = default;
		~Player() = default;

		Player(const Player& other) = delete;
		Player(Player&& other) noexcept = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) noexcept = delete;

		void InitPlayer();
	private:		
		void AddRequiredComponents();

	};
}
