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
		m_KeyStatesMap[e.key.keysym.scancode] = KeyState::Down;
		for (const auto& [keyboardKey, command] : m_KeyCommandsMap)
		{
			if (keyboardKey.first == e.key.keysym.scancode && keyboardKey.second == KeyState::Down)
			{
				command->Execute();
			}
		}
		break;
	case SDL_KEYUP:
		m_KeyStatesMap[e.key.keysym.scancode] = KeyState::Up;
		for (const auto& [keyboardKey, command] : m_KeyCommandsMap)
		{
			if (keyboardKey.first == e.key.keysym.scancode && keyboardKey.second == KeyState::Up)
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
	for (const auto& [keyboardKey, command] : m_KeyCommandsMap)
	{
		if (m_pKeyboardState[keyboardKey.first])
		{
			if (m_KeyStatesMap[keyboardKey.first] != KeyState::Pressed)
			{
				command->Execute();
			}
			m_KeyStatesMap[keyboardKey.first] = KeyState::Pressed;
		}
		else
		{
			m_KeyStatesMap[keyboardKey.first] = KeyState::Up;
		}
	}
}

void Keyboard::AttachCommandToButton(std::unique_ptr<Command> command, const KeyboardKey& key)
{
	m_KeyCommandsMap[key] = std::move(command);
	m_KeyStatesMap[key.first] = KeyState::Up;
}