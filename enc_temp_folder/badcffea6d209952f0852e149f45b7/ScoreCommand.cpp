#include "ScoreCommand.h"

#include "GameObject.h"
#include "Score.h"

#include "InputManager.h"
#include "ControllerInput.h"

#include <iostream>

using namespace dae;

dae::ScoreCommand::ScoreCommand(GameObject* gameObject, bool ignoreKeyboardInput)
    : m_pScore{ gameObject->GetComponent<Score>() }
    , m_IgnoreKeyboardInput{ ignoreKeyboardInput }
{
}

//void dae::ScoreCommand::Execute()
//{
//    auto controller = InputManager::GetInstance().GetController(0);
//    auto keyboard = InputManager::GetInstance().GetKeyboard(0);
//
//    if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonB))
//        || (!m_IgnoreKeyboardInput && keyboard->GetButtonState(SDL_SCANCODE_RIGHT) == KeyboardInput::KeyState::Pressed))
//    {
//        m_pScore->IncrementScore();
//    }
//    else if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonX))
//        || (!m_IgnoreKeyboardInput && keyboard->GetButtonState(SDL_SCANCODE_LEFT) == KeyboardInput::KeyState::Pressed))
//    {
//        m_pScore->DecrementScore();
//    }
//}
//

void dae::ScoreCommand::Execute()
{
    auto controller = InputManager::GetInstance().GetController(0);

    // Check for controller input
    if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonB)))
    {
        m_pScore->IncrementScore();
    }
    else if (controller->IsButtonPressed(static_cast<unsigned int>(ControllerInput::ControllerButtons::ButtonX)))
    {
        m_pScore->DecrementScore();
    }

    // Check for keyboard input, if not ignoring it
    if (!m_IgnoreKeyboardInput) {
        auto keyboard = InputManager::GetInstance().GetKeyboard(2);

        if (keyboard->GetButtonState(SDL_SCANCODE_RIGHT) == KeyboardInput::KeyState::Pressed)
        {
            m_pScore->IncrementScore();
        }
        else if (keyboard->GetButtonState(SDL_SCANCODE_LEFT) == KeyboardInput::KeyState::Pressed)
        {
            m_pScore->DecrementScore();
        }
    }
}
