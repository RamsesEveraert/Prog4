#pragma once
#include <SDL.h>
#include <map>
#include <memory>
#include "Command.h"

namespace dae
{
	class Keyboard
	{
	public:
		Keyboard();

		void Update(const SDL_Event& e);
		void UpdatePressed();

		void AttachCommandToButton(std::unique_ptr<Command> command, const SDL_Keycode& key);

	private:
		const Uint8* m_pState;
		std::map<SDL_Keycode, std::unique_ptr<Command>> m_KeyCommands;
	};
}


