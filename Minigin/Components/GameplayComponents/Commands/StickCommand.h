#pragma once
#include "Command.h"

namespace dae
{
	class StickCommand : public Command
	{
	public:

		virtual void Execute() override = 0;

		virtual void SetDirection(const glm::vec2& direction) = 0;
		virtual void SetSpeed(float speed) = 0;

		StickCommand() = default;
		virtual ~StickCommand() = default;

	};


}
