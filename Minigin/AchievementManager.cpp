#include "AchievementManager.h"

#include "SteamAchievements.h"

#include "EventQueue.h"
#include "Event.h"

using namespace dae;

dae::AchievementsManager::AchievementsManager()
{
	EventQueue::GetInstance().AddListener("Winner", std::bind(&AchievementsManager::SetScoreAchievements, this, std::placeholders::_1));
}

void dae::AchievementsManager::SetScoreAchievements(const Event& event)
{
	if (event.name == "Winner") SteamAchievements::GetInstance().SetAchievement(ACH_WIN_ONE_GAME);
}
