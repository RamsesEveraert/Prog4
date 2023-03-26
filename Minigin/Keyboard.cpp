#include <windows.h>
#include "Keyboard.h"

using namespace dae;

Keyboard::Keyboard()
	: m_pKeyboardState{ SDL_GetKeyboardState(nullptr) }
{
}

void Keyboard::Update(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		for (const auto& [keyboardKey, command] : m_KeyCommandsMapDown)
		{
			if (keyboardKey.first == e.key.keysym.scancode)
			{
				command->Execute();
			}
		}
		break;
	case SDL_KEYUP:
		for (const auto& [keyboardKey, command] : m_KeyCommandsMapUp)
		{
			if (keyboardKey.first == e.key.keysym.scancode)
			{
				command->Execute();
			}
		}
		break;
	default:
		break;
	}
}

void Keyboard::UpdateWhenPressed(const SDL_Event& e)
{
	SDL_PumpEvents();
	for (const auto& [keyboardKey, command] : m_KeyCommandsMapPressed)
	{
		if (keyboardKey.first == e.key.keysym.scancode)
		{
			command->Execute();
		}
	}
}

void Keyboard::AttachCommandToButton(std::shared_ptr<Command> command, const KeyboardKey& key)
{
	switch (key.second)
	{
	case KeyState::Up:
		m_KeyCommandsMapUp[key] = std::move(command);
		break;
	case KeyState::Down:
		m_KeyCommandsMapDown[key] = std::move(command);
		break;
	case KeyState::Pressed:
		m_KeyCommandsMapPressed[key] = std::move(command);
		break;
	}
}