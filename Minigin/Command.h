#pragma once

namespace dae
{
	class GameObject;
	class Command
	{
	public:
		virtual void Execute() = 0;

		Command() = default;
		virtual ~Command() = default;

		Command(const Command&) = default;
		Command(Command&&) = default;
		Command& operator=(const Command&) = default;
		Command& operator=(Command&&) = default;

	};
}
