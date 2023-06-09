#pragma once
#include "Component.h"

namespace dae
{
	class Grid;
	class Player final : public Component
	{
	public:
		Player(Grid* pGrid);
		virtual ~Player() = default;

		Player(const Player& other) = delete;
		Player(Player&& other) noexcept = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) noexcept = delete;

		void InitPlayer(bool isPlayer1);
		void ResetPlayerStartPosition();
	private:		
		void AddRequiredComponents(bool isPlayer1);

		Grid* m_pGrid;

	};
}
