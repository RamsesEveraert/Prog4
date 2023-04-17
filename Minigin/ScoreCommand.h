#pragma once

#include "Command.h"

namespace dae
{
	class Score;
	class ScoreCommand final : public Command
	{
	public:

		enum class InputType
		{
			Keyboard, Controller
		};

		ScoreCommand(GameObject* gameObject, int playerIdx, InputType inputType);
		~ScoreCommand() = default;

		virtual void Execute() override;
	private:
		Score* m_pScore;
		int m_PlayerIdx;
		InputType m_InputType;
	};

}

