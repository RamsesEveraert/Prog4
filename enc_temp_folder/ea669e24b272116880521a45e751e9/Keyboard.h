#pragma once
#include <SDL.h>
#include <map>
#include <memory>
#include "Command.h"

namespace dae
{
	class Keyboard final
	{
	public:
		enum class KeyState {
			Up, Down, Pressed
		};

		Keyboard();

		void Update(const SDL_Event& e);
		void UpdateWhenPressed();

		using KeyboardKey = std::pair<SDL_Scancode, KeyState>;

		void AttachCommandToButton(std::unique_ptr<Command> command, const KeyboardKey& key);

	private:
		const Uint8* m_pState;
		std::map<KeyboardKey, std::unique_ptr<Command>> m_KeyCommands;
		std::map<SDL_Scancode, KeyState> m_KeyStates;
	};
}