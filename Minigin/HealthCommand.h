#pragma once

#include "Command.h"

namespace dae
{
	class Health;
	class HealthCommand final : public Command
	{
	public:
		HealthCommand(GameObject* gameObject);
		~HealthCommand() = default;

		virtual void Execute() override;
	private:
		Health* m_pHealth;
	};

}

