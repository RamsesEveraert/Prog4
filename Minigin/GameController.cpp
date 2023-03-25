#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "GameController.h"
#include "Command.h"

using namespace dae;

class GameController::GameControllerImpl
{
public:
	GameControllerImpl(int controllerIndex)
		:m_ControllerIndex(controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	void ExecuteCommands()
	{

		for (const auto& command : m_ControllerCommands)
		{
			switch (command.first.second) 
			{
			case dae::GameController::ButtonState::Up:
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

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

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

	void AttachCommandToButton(std::unique_ptr<Command> command, ControllerButton button)
	{
		m_ControllerCommands.insert(std::pair<ControllerButton, std::unique_ptr<Command>>(button, std::move(command)));
	}

	void DetachCommandFromButton(ControllerButton button)
	{
		auto it = m_ControllerCommands.find(button);
		if (it != m_ControllerCommands.end())
		{
			m_ControllerCommands.erase(it);
		}
	}

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	using ControllerCommandsMap = std::map<ControllerButton, std::unique_ptr<Command>>;
	ControllerCommandsMap m_ControllerCommands;

	const int m_ControllerIndex;
};



GameController::GameController(int controllerIndex)
	:m_pImplController(new GameControllerImpl{ controllerIndex })
{
}

dae::GameController::~GameController()
{
	delete m_pImplController;
}

void GameController::Update()
{

	m_pImplController->Update();

}

bool GameController::IsDown(unsigned int button) const
{
	return m_pImplController->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool GameController::IsUp(unsigned int button) const
{
	return m_pImplController->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool GameController::IsPressed(unsigned int button) const
{

	return m_pImplController->IsPressed(static_cast<unsigned int>(button));
}

void dae::GameController::AttachCommandToButton(std::unique_ptr<Command> command, ControllerButton button)
{
	m_pImplController->AttachCommandToButton(std::move(command), button);
}

void dae::GameController::DetachCommandFromButton(ControllerButton button)
{
	m_pImplController->DetachCommandFromButton(button);
}