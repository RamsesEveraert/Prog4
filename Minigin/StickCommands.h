#pragma once
#include "Command.h"

namespace dae
{
	class StickCommands : public Command
	{
	public:

		virtual void Execute() override = 0;

		virtual void SetDirection(const glm::vec2& direction) = 0;

		StickCommands() = default;
		virtual ~StickCommands() = default;

	protected:

	private:
	};

	
}
