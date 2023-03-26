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


void Keyboard::UpdateWhenPressed()
{
	SDL_PumpEvents();
	for (const auto& [keyboardKey, command] : m_KeyCommandsMapPressed)
	{
		if (m_pKeyboardState[keyboardKey.first])
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
		m_KeyCommandsMapUp[key] = command;
		break;
	case KeyState::Down:
		m_KeyCommandsMapDown[key] = command;
		break;
	case KeyState::Pressed:
		m_KeyCommandsMapPressed[key] = command;
		break;
	}
}

void Keyboard::DetachCommandFromButton(std::shared_ptr<Command> command, const KeyboardKey& key)
{
	switch (key.second)
	{
	case KeyState::Up:
		m_KeyCommandsMapUp.erase(key);
		break;
	case KeyState::Down:
		m_KeyCommandsMapDown.erase(key);
		break;
	case KeyState::Pressed:
		m_KeyCommandsMapPressed.erase(key);
		break;
	}
}