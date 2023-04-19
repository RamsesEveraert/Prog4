#include "AchievementManager.h"

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

void dae::AchievementsManager::SetScoreAchievements(const Event& )
{
    
}
