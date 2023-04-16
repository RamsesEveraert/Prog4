#include "HealthCommand.h"

#include "GameObject.h"
#include "Health.h"

#include "InputManager.h"
#include "KeyboardInput.h"
#include <SDL.h>

#include <iostream>

using namespace dae;

dae::HealthCommand::HealthCommand(GameObject* gameObject)
	: m_pHealth{gameObject->GetComponent<Health>()}
{
}

void dae::HealthCommand::Execute()
{
    auto keyboard = InputManager::GetInstance().GetKeyboard();
    if (keyboard->GetButtonState(SDL_SCANCODE_LEFT) == KeyboardInput::KeyState::Pressed)
    {
        std::cout << "Hit pressed! \n";
        m_pHealth->Hit();
    }
    else if (keyboard->GetButtonState(SDL_SCANCODE_RIGHT) == KeyboardInput::KeyState::Pressed)
    {
        std::cout << "heal pressed! \n";
        m_pHealth->Heal();
    }
}
