#include "NextLevelCommand.h"

#include "Event.h"
#include "EventHandler.h"

#include <iostream>

void dae::NextLevelCommand::Execute()
{
	Event nextLevel{ "NextLevel", {  } };
	EventHandler::GetInstance().Dispatch(nextLevel);
	/*int nextLevel{ (m_CurrentLevel >= 3) ? 1 : m_CurrentLevel + 1 };
	auto& level = dae::SceneManager::GetInstance().CreateScene("NextLevel");
	LevelManager::GetInstance().LoadLevel(level, m_CurrentMode, nextLevel);
	std::cout << "current level: " << std::to_string(nextLevel) << "\n";*/
}
