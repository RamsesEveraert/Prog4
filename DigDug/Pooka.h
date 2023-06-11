#pragma once
#include "Enemies/Enemy.h"

#include "PookaStateInterface.h"


namespace dae
{
	class Transform;
	class GameObject;
	class Grid;
	class Pooka final : public Component
	{
	public:
		Pooka(GameObject* player, Grid* pGrid, int indexEnemy);
		~Pooka() = default;

		void Initialize();

		virtual void Update() override;
	private:
		void ChangeState(std::unique_ptr<PookaStateInterface> pState);

		std::unique_ptr<PookaStateInterface> m_pState;
		GameObject* m_pPlayer;
		Grid* m_pGrid;
		int m_IndexEnemy;
	};
}


