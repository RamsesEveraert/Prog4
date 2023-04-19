#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>


#include <iostream>

using namespace dae;

bool InputManager::ProcessInput()
{
	// update keyboard 

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}		

		for (auto& keyboard : m_Keyboards)
		{
			keyboard->Update(e);
		}	

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (auto& keyboard : m_Keyboards)
	{
		keyboard->UpdateWhenPressed();
	}

	// update controllers

	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	return true;
}

ControllerInput* InputManager::AddController()
{
	const int idx{ static_cast<int>(m_Controllers.size()) };
	m_Controllers.push_back(std::make_unique<ControllerInput>(idx));

	return m_Controllers[idx].get();
}

KeyboardInput* dae::InputManager::AddKeyboard()
{
	const int idx{ static_cast<int>(m_Keyboards.size()) };
	m_Keyboards.push_back(std::make_unique<KeyboardInput>(idx));

	return m_Keyboards[idx].get();
}

KeyboardInput* dae::InputManager::GetKeyboard(int idx)
{
	if (idx >= 0 && idx < static_cast<int>( m_Controllers.size()))
	{
		return m_Keyboards[idx].get();
	}
	else
	{
		std::cout << "Error: Keyboard index out of range.\n";
		return nullptr;
	}
}

ControllerInput* InputManager::GetController(int idx)
{
	if (idx >= 0 && idx < static_cast<int>(m_Controllers.size()))
	{
		return m_Controllers[idx].get();
	}
	else
	{
		std::cout << "Error: Controller index out of range.\n";
		return nullptr;
	}
}


