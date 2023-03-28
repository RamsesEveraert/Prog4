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
		KeyboardInput* GetKeyboard();

		int GetAmountOfControllers() const { return static_cast<int>(m_Controllers.size()); }

	private:

		std::vector<std::unique_ptr<ControllerInput>> m_Controllers{};
		std::unique_ptr<KeyboardInput>m_pKeyboard = std::make_unique<KeyboardInput>();

	};

}
