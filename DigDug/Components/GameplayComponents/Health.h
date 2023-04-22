#pragma once
#include "Component.h"

namespace dae
{
	class Health final : public Component
	{
	public:
		Health();
		~Health() = default;

		void Hit();
		void Heal();

		void SetHealth(int health);
		int GetHealth() const;

	private:
		int m_Health;
	};
}


