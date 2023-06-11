#pragma once
#include "Command.h"

namespace dae
{
	enum class GameMode;
	class Scene;
	class NextLevelCommand final : public Command
	{
	public:
		NextLevelCommand() = default;
		~NextLevelCommand() = default;

		virtual void Execute() override;
	private:
	};

}

