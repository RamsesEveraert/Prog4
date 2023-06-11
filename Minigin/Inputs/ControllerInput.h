#pragma once
#include "Command.h"
#include "StickCommand.h"
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <glm/glm.hpp>


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

		using Button = std::pair<ControllerInput::ControllerButtons, ControllerInput::ButtonState>;

		void AttachCommandToButton(std::shared_ptr<Command> command, const Button& button);
		void DetachCommandFromButton(const Button& button);

		void AttachCommandToThumbStick(std::shared_ptr<StickCommand> command, const ControllerButtons& button);
		void DetachCommandToThumbStick( const ControllerButtons& button);

		void AttachCommandToTrigger(std::shared_ptr<Command> command, const ControllerButtons& button);
		void DetachCommandToTrigger(const ControllerButtons& button);

		bool IsButtonPressed(unsigned int button) const;

		const glm::vec2& GetDirectionLeftThumbStick() const;
		const glm::vec2& GetDirectionRightThumbStick() const;

		void ClearCommands();
		

		explicit ControllerInput(int controllerIndex, bool inertYAxis = true);
		~ControllerInput();
		ControllerInput(const ControllerInput& other) = delete;
		ControllerInput(ControllerInput&& other) = delete;
		ControllerInput& operator=(const ControllerInput& other) = delete;
		ControllerInput& operator=(ControllerInput&& other) = delete;

	private:

		class GameControllerImpl;
		GameControllerImpl* m_pImplController;
		
	};
}
