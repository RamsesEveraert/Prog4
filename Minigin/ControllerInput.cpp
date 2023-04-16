#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "ControllerInput.h"
#include "Command.h"
#include "MoveCommand.h"

#include <string>
#include <algorithm>


using namespace dae;

class ControllerInput::GameControllerImpl
{
public:
	GameControllerImpl(int controllerIndex, bool invertYAxis)
		: m_ControllerIndex(controllerIndex)
		, m_Deadzone{ 0.2f }
		, m_InvertYAxis {invertYAxis}
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	void ExecuteCommands()
	{

		for (const auto& command : m_ButtonCommands)
		{
			switch (command.first.second)
			{
			case dae::ControllerInput::ButtonState::Up:
				if (IsDownThisFrame(static_cast<unsigned int>(command.first.first)))
				{
					command.second->Execute();
				}
				break;

			case ButtonState::Down:
				if (IsUpThisFrame(static_cast<unsigned int>(command.first.first)))
				{
					command.second->Execute();
				}
				break;

			case ButtonState::Pressed:
				if (IsPressed(static_cast<unsigned int>(command.first.first)))
				{
					command.second->Execute();
				}
				break;
			}
		}
	}

	const glm::vec2& GetDirectionLeftThumbStick() const
	{
		return m_LeftStickDirection;
	}

	const glm::vec2& GetDirectionRightThumbStick() const
	{
		return m_RightStickDirection;
	}

	void ApplyDeadZoneSticks(glm::vec2& stickDirection)
	{
		// Read the thumbstick values and applies the deadzone pattern: https://www.gamedeveloper.com/disciplines/doing-thumbstick-dead-zones-right
		const float magnitude = glm::length(stickDirection);
		if (magnitude > m_Deadzone) {
			stickDirection = glm::normalize(stickDirection) * ((magnitude - m_Deadzone) / (1 - m_Deadzone)); // normalize for correct deadzone
			stickDirection = magnitude > 1.0f ? glm::normalize(stickDirection) : stickDirection;
		}
		else stickDirection = glm::vec2{ 0.0f, 0.0f };
	}

	void ApplyDeadZoneTriggers(float& triggerValue)
	{
		if (triggerValue > m_Deadzone) triggerValue = (triggerValue - m_Deadzone) / (1 - m_Deadzone);
		else triggerValue = 0.0f;		
	}

	void UpdateThumbSticks()
	{
		// Apply deadzone to left stick
		m_LeftStickDirection.x = static_cast<float>(m_CurrentState.Gamepad.sThumbLX) / SHRT_MAX; // get right values [-1,1]
		m_LeftStickDirection.y = static_cast<float>(m_CurrentState.Gamepad.sThumbLY) / SHRT_MAX;
		ApplyDeadZoneSticks(m_LeftStickDirection);

		// Apply deadzone to right stick
		m_RightStickDirection.x = static_cast<float>(m_CurrentState.Gamepad.sThumbRX) / SHRT_MAX;
		m_RightStickDirection.y = static_cast<float>(m_CurrentState.Gamepad.sThumbRY) / SHRT_MAX;
		ApplyDeadZoneSticks(m_RightStickDirection);

		for (const auto& command : m_StickCommandMap)
		{
			if (m_LeftStickDirection != glm::vec2{ 0,0 })
			{
				if (m_InvertYAxis) m_LeftStickDirection.y *= -1;
				command.second->SetDirection(m_LeftStickDirection);
				command.second->Execute();
			}
		}
	}

	void UpdateTriggers()
	{
		float maxValueBit{ 255.f };

		// Apply deadzone to left and right triggers
		float leftTrigger = static_cast<float>(m_CurrentState.Gamepad.bLeftTrigger) / maxValueBit;
		ApplyDeadZoneTriggers(leftTrigger);

		float rightTrigger = static_cast<float>(m_CurrentState.Gamepad.bRightTrigger) / maxValueBit;
		ApplyDeadZoneTriggers(rightTrigger);

		// Execute commands attached to button triggers
		for (const auto& command : m_TriggerCommandMap)
		{
			if (command.first == ControllerButtons::LeftBumper && leftTrigger > 0.f)
			{
				std::cout << "Left trigger activated with value " << std::to_string(leftTrigger) << "\n";
				command.second->Execute();
			}
			else if (command.first == ControllerButtons::RightBumper && rightTrigger > 0.f)
			{
				std::cout << "Right trigger activated with value " << std::to_string(rightTrigger) << "\n";
				command.second->Execute();
			}
		}
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		UpdateThumbSticks();
		UpdateTriggers();

		ExecuteCommands();
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	void AttachCommandToButton(std::shared_ptr<Command> command,const Button & button)
	{
		m_ButtonCommands.insert(std::pair<Button, std::shared_ptr<Command>>(button, command));
	}

	void AttachCommandToThumbStick(std::shared_ptr<StickCommand> command, const ControllerButtons& button)
	{
		m_StickCommandMap.insert(std::make_pair(button, command));
	}

	void AttachCommandToTrigger(std::shared_ptr<Command> command, const ControllerButtons& button)
	{
		m_TriggerCommandMap.insert(std::make_pair(button, command));
	}

	void DetachCommandFromButton(const Button& button)
	{
		auto it = m_ButtonCommands.find(button);
		if (it != m_ButtonCommands.end())
		{
			m_ButtonCommands.erase(it);
		}
	}

	void DetachCommandFromThumbStick(const ControllerButtons& button)
	{
		auto it = m_StickCommandMap.find(button);
		if (it != m_StickCommandMap.end())
		{
			m_StickCommandMap.erase(it);
		}
	}

	void DetachCommandToTrigger(const ControllerButtons& button)
	{
		auto it = m_TriggerCommandMap.find(button);
		if (it != m_TriggerCommandMap.end())
		{
			m_TriggerCommandMap.erase(it);
		}
	}


private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	using ControllerCommandsMap = std::map<Button, std::shared_ptr<Command>>;
	ControllerCommandsMap m_ButtonCommands{};

	std::map<ControllerButtons, std::shared_ptr<StickCommand>> m_StickCommandMap{};
	std::map<ControllerButtons, std::shared_ptr<Command>> m_TriggerCommandMap{};

	const int m_ControllerIndex;

	glm::vec2 m_LeftStickDirection{};
	glm::vec2 m_RightStickDirection{};

	const float m_Deadzone;

	bool m_InvertYAxis;
};



ControllerInput::ControllerInput(int controllerIndex, bool invertYAxis)
	:m_pImplController(new GameControllerImpl{ controllerIndex, invertYAxis })
{
}

dae::ControllerInput::~ControllerInput()
{
	delete m_pImplController;
}

void ControllerInput::Update()
{

	m_pImplController->Update();

}

void dae::ControllerInput::AttachCommandToButton(std::shared_ptr<Command> command, const Button& button)
{
	m_pImplController->AttachCommandToButton(command, button);
}

void dae::ControllerInput::DetachCommandFromButton(const Button& button)
{
	m_pImplController->DetachCommandFromButton(button);
}

void dae::ControllerInput::AttachCommandToThumbStick(std::shared_ptr<StickCommand> command, const ControllerButtons& button)
{
	m_pImplController->AttachCommandToThumbStick(command, button);
}

void dae::ControllerInput::DetachCommandToThumbStick(const ControllerButtons& button)
{
	m_pImplController->DetachCommandFromThumbStick(button);
}

void dae::ControllerInput::AttachCommandToTrigger(std::shared_ptr<Command> command, const ControllerButtons& button)
{
	m_pImplController->AttachCommandToTrigger(command,button);
}

void dae::ControllerInput::DetachCommandToTrigger(const ControllerButtons& button)
{
	m_pImplController->DetachCommandToTrigger(button);
}

const glm::vec2& dae::ControllerInput::GetDirectionLeftThumbStick() const
{
	return m_pImplController->GetDirectionLeftThumbStick();
}

const glm::vec2& dae::ControllerInput::GetDirectionRightThumbStick() const
{
	return m_pImplController->GetDirectionRightThumbStick();
}
