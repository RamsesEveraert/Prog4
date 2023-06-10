#pragma once
#include "PookaStateInterface.h"

#include "Grid.h"

#include <glm/glm.hpp>



namespace dae
{
	class Grid;
	class GameObject;
	class PookaNormalState final : public PookaStateInterface
	{
	public:
		PookaNormalState(GameObject* pPooka, GameObject* pPlayer, Grid* pGrid);

		virtual void OnEnter() override;
		virtual void OnEnd() override;

		virtual std::unique_ptr<PookaStateInterface> Update();

	private:

		void UpdateMovement();
		bool CanMove(const glm::vec2& pookaPosition);
		glm::vec2 GetRandomDirection() const;

		GameObject* m_pPooka;
		GameObject* m_pPlayer;
		Grid* m_pGrid;

		const float m_GhostTime;
		float m_NormalTime, m_TransitionTime;
		float m_HuntRange;
		float m_Speed;

		glm::vec2 m_PookaDirection;

		Grid::Cell m_CurrentCell, m_TargetCell;

	};
}


