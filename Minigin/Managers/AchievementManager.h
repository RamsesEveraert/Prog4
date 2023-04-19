#pragma once
#include <string>
namespace dae
{
    struct Event;
    class AchievementsManager final
    {
    public:
        AchievementsManager();
        ~AchievementsManager();
        AchievementsManager(const AchievementsManager& other) = default;
        AchievementsManager(AchievementsManager&& other) = default;
        AchievementsManager& operator=(const AchievementsManager& other) = default;
        AchievementsManager& operator=(AchievementsManager&& other) = default;

        void SetScoreAchievements(const Event& event);
    };
}


