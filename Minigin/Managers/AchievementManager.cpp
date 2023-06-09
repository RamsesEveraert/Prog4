#include "AchievementManager.h"

#include "EventHandler.h"
#include "Event.h"

#include <iostream>

using namespace dae;

dae::AchievementsManager::AchievementsManager()
{
    EventHandler::GetInstance().AddListener("IncrementScore", [this](const dae::Event& event) { SetScoreAchievements(event); });
}
dae::AchievementsManager::~AchievementsManager()
{
    EventHandler::GetInstance().RemoveListener("IncrementScore", [this](const dae::Event& event) { SetScoreAchievements(event); });
}

void dae::AchievementsManager::SetScoreAchievements(const Event& )
{
    
}
