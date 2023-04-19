#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Health final : public BaseComponent
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


