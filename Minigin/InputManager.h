#pragma once
#include "Singleton.h"
#include <windows.h>
#include <XInput.h>

#include "GameController.h"

#include <vector>
#include <map>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		GameController* AddController();
		int GetAmountOfControllers() const { return static_cast<int>(m_Controllers.size()); }

	private:

		std::vector<std::unique_ptr<GameController>> m_Controllers{};

	};

}
