#pragma once

#include "Command.h"

namespace dae
{
	class Health;
	class GameObject;
	class HealthCommand final : public Command
	{
	public:

		enum class InputType
		{
			Keyboard, Controller
		};

		HealthCommand(GameObject* gameObject, int playerIdx, InputType inputType);
		~HealthCommand() = default;

		virtual void Execute() override;
	private:
		Health* m_pHealth;
		int m_PlayerIdx;
		InputType m_InputType;
		GameObject* m_pGameObject;
	};

}

