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

		m_pKeyboard->Update(e);			

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_pKeyboard->UpdateWhenPressed();

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

KeyboardInput* dae::InputManager::GetKeyboard()
{
	return m_pKeyboard.get();
}

