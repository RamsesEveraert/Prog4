#pragma once
#include "Component.h"

namespace dae
{
	struct Event;
	class Player;
	class Enemy;
	class GameObject;
	class Health final : public Component
	{
	public:
		Health();
		~Health() = default;

		void Initialize();
		void OnHit(const dae::Event& event);
		void HitPlayer();
		void HitEnemy();
		void Heal();

		void SetHealth(int health);
		int GetHealth() const;

	private:
		int m_Health;
		Player* m_pPlayer;
		Enemy* m_pEnemy;
		GameObject* m_pOwner;
	};
}


