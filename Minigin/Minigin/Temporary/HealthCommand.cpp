//#include "HealthCommand.h"
//
//#include "GameObject.h"
//#include "Health.h"
//
//#include "InputManager.h"
//#include "KeyboardInput.h"
//#include <SDL.h>
//
//#include <iostream>
//
//using namespace dae;
//
//dae::HealthCommand::HealthCommand(GameObject* gameObject, int playerIdx, InputType inputType)
//	: m_pHealth{gameObject->GetComponent<Health>()}
//    , m_PlayerIdx { playerIdx }
//    , m_InputType {inputType}
//    , m_pGameObject {gameObject}
//{
//}
//
//void dae::HealthCommand::Execute()
//{
//    if (m_InputType == InputType::Keyboard)
//    {
//        auto keyboard = InputManager::GetInstance().GetKeyboard(m_PlayerIdx);
//        if (keyboard->GetButtonState(SDL_SCANCODE_UP) == KeyboardInput::KeyState::Pressed)
//        {
//            m_pHealth->Heal();
//        }
//        else if (keyboard->GetButtonState(SDL_SCANCODE_DOWN) == KeyboardInput::KeyState::Pressed)
//        {
//            m_pHealth->Hit();
//        }
//    }
//    else if (m_InputType == InputType::Controller)
//    {
//        auto controller = InputManager::GetInstance().GetController(m_PlayerIdx);
//        if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonY)))
//        {
//            m_pHealth->Heal();
//        }
//        else if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonA)))
//        {
//            m_pHealth->Hit();
//        }
//    }
//}
//
