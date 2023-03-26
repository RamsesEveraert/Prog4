#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Keyboard.h"

using namespace dae;

Keyboard::Keyboard()
	: m_pState{ SDL_GetKeyboardState(nullptr) }
{
}

void Keyboard::Update(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		m_KeyStates[e.key.keysym.scancode] = KeyState::Down;
		for (const auto& [keyboardKey, command] : m_KeyCommands)
		{
			if (keyboardKey.first == e.key.keysym.scancode && keyboardKey.second == KeyState::Down)
			{
				command->Execute();
			}
		}
		break;
	case SDL_KEYUP:
		m_KeyStates[e.key.keysym.scancode] = KeyState::Up;
		for (const auto& [keyboardKey, command] : m_KeyCommands)
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
	for (const auto& [keyboardKey, command] : m_KeyCommands)
	{
		if (m_pState[keyboardKey.first])
		{
			if (m_KeyStates[keyboardKey.first] != KeyState::Pressed)
			{
				command->Execute();
			}
			m_KeyStates[keyboardKey.first] = KeyState::Pressed;
		}
		else
		{
			m_KeyStates[keyboardKey.first] = KeyState::Up;
		}
	}
}


void Keyboard::AttachCommandToButton(std::unique_ptr<Command> command, const KeyboardKey& key)
{
	m_KeyCommands[key] = std::move(command);
	m_KeyStates[key.first] = KeyState::Up;
}