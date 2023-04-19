//#include "ScoreCommand.h"
//
//#include "GameObject.h"
//#include "Score.h"
//
//#include "InputManager.h"
//#include "ControllerInput.h"
//
//#include <iostream>
//
//using namespace dae;
//
//dae::ScoreCommand::ScoreCommand(GameObject* gameObject, int playerIdx, InputType inputType)
//    : m_pScore{ gameObject->GetComponent<Score>() }
//    , m_PlayerIdx{ playerIdx }
//    , m_InputType {inputType} 
//{
//}
//
//void dae::ScoreCommand::Execute()
//{
//    if (m_InputType == InputType::Keyboard)
//    {
//        auto keyboard = InputManager::GetInstance().GetKeyboard(m_PlayerIdx);
//        if (keyboard->GetButtonState(SDL_SCANCODE_RIGHT) == KeyboardInput::KeyState::Pressed)
//        {
//            m_pScore->IncrementScore();
//        }
//        else if (keyboard->GetButtonState(SDL_SCANCODE_LEFT) == KeyboardInput::KeyState::Pressed)
//        {
//            m_pScore->DecrementScore();
//        }
//    }
//    else if (m_InputType == InputType::Controller)
//    {
//        auto controller = InputManager::GetInstance().GetController(m_PlayerIdx);
//        if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonB)))
//        {
//            m_pScore->IncrementScore();
//        }
//        else if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonX)))
//        {
//            m_pScore->DecrementScore();
//        }
//    }
//}