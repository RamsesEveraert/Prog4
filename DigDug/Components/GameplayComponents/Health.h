#pragma once
#include "Component.h"

namespace dae
{
	struct Event;
	class Health final : public Component
	{
	public:
		Health();
		~Health() = default;

		void OnHit(const dae::Event& event);
		void Heal();

		void SetHealth(int health);
		int GetHealth() const;

	private:
		int m_Health;
	};
}


