#include <windows.h>
#include "KeyboardInput.h"

#include <iostream>

using namespace dae;

KeyboardInput::KeyboardInput(int idx)
	: m_pKeyboardState{ SDL_GetKeyboardState(nullptr) }
	, m_KeyboardIndex{idx}
{
}

void KeyboardInput::Update(const SDL_Event& e)
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


void KeyboardInput::UpdateWhenPressed()
{
	SDL_PumpEvents();
	for (const auto& [keyboardKey, command] : m_KeyCommandsMapPressed)
	{
		if (m_pKeyboardState[keyboardKey.first])
		{
			if(command)
			command->Execute();
		}
	}
}





void KeyboardInput::AttachCommandToButton(std::shared_ptr<Command> command, const KeyboardKey& key)
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

void KeyboardInput::DetachCommandFromButton(std::shared_ptr<Command> command, const KeyboardKey& key)
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

void dae::KeyboardInput::ClearCommands()
{
	m_KeyCommandsMapPressed.clear();
	m_KeyCommandsMapDown.clear();
	m_KeyCommandsMapUp.clear();
}

KeyboardInput::KeyState KeyboardInput::GetButtonState(SDL_Scancode key) const
{
	if (m_pKeyboardState[key])
	{
		return KeyboardInput::KeyState::Pressed;
	}
	else
	{
		return KeyboardInput::KeyState::Up;
	}
}