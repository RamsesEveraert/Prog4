#pragma once

#include "Command.h"

namespace dae
{
	class Score;
	class ScoreCommand final : public Command
	{
	public:
		ScoreCommand(GameObject* gameObject, bool ignoreKeyboardInput);
		~ScoreCommand() = default;

		virtual void Execute() override;
	private:
		Score* m_pScore;
		bool m_IgnoreKeyboardInput;
	};

}

