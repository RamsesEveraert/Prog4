#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Keyboard.h"

#include <iostream>

using namespace dae;

Keyboard::Keyboard()
	: m_pState{ SDL_GetKeyboardState(nullptr) }
{
}

void Keyboard::Update(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		
		const auto key{ e.key.keysym.sym };
		const auto commandIt{ m_KeyCommands.find(key) };
		if (commandIt != m_KeyCommands.end())
		{
			commandIt->second->Execute();
		}
	}

	if (e.type == SDL_KEYUP)
	{
		// werkt
		const auto key{ e.key.keysym.sym };
		const auto commandIt{ m_KeyCommands.find(key) };
		if (commandIt != m_KeyCommands.end())
		{
			commandIt->second->Execute();
		}
	}
}

void Keyboard::UpdatePressed()
{
	SDL_PumpEvents();
	m_pState = SDL_GetKeyboardState(nullptr);

	for (const auto& key : m_KeyCommands)
	{
		const auto& [button, command] { key };
		if (command && m_pState[SDL_GetScancodeFromKey(button)])
		{
			command->Execute();
		}
	}
}


void Keyboard::AttachCommandToButton(std::unique_ptr<Command> command, const SDL_Keycode & key)
{
	m_KeyCommands[key] = std::move(command);
}