#pragma once
#include "Singleton.h"
#include "GameController.h"
#include "Keyboard.h"

#include <vector>
#include <map>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		GameController* AddController();
		Keyboard* GetKeyboard();

		int GetAmountOfControllers() const { return static_cast<int>(m_Controllers.size()); }

	private:

		std::vector<std::unique_ptr<GameController>> m_Controllers{};
		std::unique_ptr<Keyboard>m_pKeyboard = std::make_unique<Keyboard>();

	};

}
