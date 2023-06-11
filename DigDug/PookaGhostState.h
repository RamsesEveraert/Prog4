#pragma once
#include "PookaStateInterface.h"

namespace dae
{
	class GameObject;
	class Grid;
	class Transform;
	class PookaGhostState final : public PookaStateInterface
	{
	public:
		PookaGhostState(GameObject* pPooka, GameObject* pPlayer, Grid* pGrid);

		virtual void OnEnter() override;
		virtual void OnEnd() override;

		virtual std::unique_ptr<PookaStateInterface> Update();

	private:
		GameObject* m_pPooka;
		GameObject* m_pPlayer;
		Grid* m_pGrid;
		Transform* m_pPookaTransform;
		float m_GhostFormTime;
		const float m_TransitionTime, m_Speed;
	};

}

