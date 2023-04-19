#pragma once
#include <SDL.h>
#include <map>
#include <memory>
#include "Command.h"

namespace dae
{
	class KeyboardInput final
	{
	public:
		enum class KeyState {
			Up, Down, Pressed
		};

		KeyboardInput(int idx);

		void Update(const SDL_Event& e);
		void UpdateWhenPressed();

		using KeyboardKey = std::pair<SDL_Scancode, KeyState>;

		void AttachCommandToButton(std::shared_ptr<Command> command, const KeyboardKey& key);
		void DetachCommandFromButton(std::shared_ptr<Command> command, const KeyboardKey& key);

		KeyboardInput::KeyState GetButtonState(SDL_Scancode key) const;
		

	private:
		const Uint8* m_pKeyboardState;
		const int m_KeyboardIndex;
		std::map<KeyboardKey, std::shared_ptr<Command>> m_KeyCommandsMapPressed;
		std::map<KeyboardKey, std::shared_ptr<Command>> m_KeyCommandsMapUp;
		std::map<KeyboardKey, std::shared_ptr<Command>> m_KeyCommandsMapDown;

	};
}