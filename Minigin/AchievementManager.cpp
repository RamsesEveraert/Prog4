#include "AchievementManager.h"

#include "SteamAchievements.h"

#include "EventQueue.h"
#include "Event.h"

#include <iostream>

using namespace dae;

dae::AchievementsManager::AchievementsManager()
{
    EventQueue::GetInstance().AddListener("IncrementScore", [this](const dae::Event& event) { SetScoreAchievements(event); });
}
dae::AchievementsManager::~AchievementsManager()
{
    EventQueue::GetInstance().RemoveListener("IncrementScore", [this](const dae::Event& event) { SetScoreAchievements(event); });
}

void dae::AchievementsManager::SetScoreAchievements(const Event& event)
{
    int score{};
    for (const auto& data : event.data)
    {
        if (data.type() == typeid(int))
        {
            score = std::any_cast<int>(data);
        }
    }
	if (score == 500) SteamAchievements::GetInstance().SetAchievement(ACH_WIN_ONE_GAME);
}
