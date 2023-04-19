#pragma once
#include "Singleton.h"
#include "ControllerInput.h"
#include "KeyboardInput.h"

#include <vector>
#include <map>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		ControllerInput* AddController();
		KeyboardInput* AddKeyboard();
		KeyboardInput* GetKeyboard(int idx);
		ControllerInput* GetController(int idx);

		int GetAmountOfControllers() const { return static_cast<int>(m_Controllers.size()); }

	private:

		std::vector<std::unique_ptr<ControllerInput>> m_Controllers{};
		std::vector<std::unique_ptr<KeyboardInput>> m_Keyboards{};

	};

}
