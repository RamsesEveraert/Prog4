#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

//#include <windows.h>
//#include <XInput.h>
#include <iostream>

using namespace dae;

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	
	// update controllers

	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	return true;
}

GameController* InputManager::AddController()
{
	const int idx{ static_cast<int>(m_Controllers.size()) };
	m_Controllers.push_back(std::make_unique<GameController>(idx));

	return m_Controllers[idx].get();
}

