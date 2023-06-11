#pragma once
#include "PookaStateInterface.h"

// components
#include "Grid.h"

// states
#include "PookaGhostState.h"

//singleton
#include "Timer.h"

#include <glm/glm.hpp>



namespace dae
{
	struct Event;
	class Grid;
	class Transform;
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
		void onCantMove(const Event& event);
		glm::vec2 GetRandomDirection() const;

		GameObject* m_pPooka;
		GameObject* m_pPlayer;
		Transform* m_pPookaTransform;
		Grid* m_pGrid;

		const float m_GhostTime;
		float m_NormalTime, m_TransitionTime;
		float m_HuntRange;
		float m_Speed;

		glm::vec2 m_PookaDirection;

		Grid::Cell m_CurrentCell, m_TargetCell;
		std::vector<Grid::Cell> m_Cells;

	};
}


