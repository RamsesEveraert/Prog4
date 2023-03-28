#pragma once
#include "Command.h"
#include <memory>
#include <vector>
#include <map>
#include <iostream>


namespace dae
{
	class ControllerInput final
	{
	public:
		

		enum class ControllerButtons
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,

			Start = 0x0010,
			Back = 0x0020,

			LeftThumbstick = 0x0040,
			RightThumbstick = 0x0080,

			LeftBumper = 0x0100,
			RightBumper = 0x0200,

			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		enum class ButtonState
		{
			Up, Down, Pressed
		};

		void Update();

		using ControllerButton = std::pair<ControllerInput::ControllerButtons, ControllerInput::ButtonState>;

		void AttachCommandToButton(std::shared_ptr<Command> command, const ControllerButton& button);
		void DetachCommandFromButton(const ControllerButton& button);
		

		explicit ControllerInput(int controllerIndex);
		~ControllerInput();
		ControllerInput(const ControllerInput& other) = delete;
		ControllerInput(ControllerInput&& other) = delete;
		ControllerInput& operator=(const ControllerInput& other) = delete;
		ControllerInput& operator=(ControllerInput&& other) = delete;

	private:

		class GameControllerImpl;
		GameControllerImpl* m_pImplController;

		bool IsDown(unsigned int button) const;
		bool IsUp(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

		
	};
}
