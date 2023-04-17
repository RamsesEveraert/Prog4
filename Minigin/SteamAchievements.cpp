#include "SteamAchievements.h"

#include "steam_api.h"

using namespace dae;

bool SteamAchievements::SetAchievement(const EAchievements& achievement)
{
    if (achievement >= static_cast<EAchievements>(m_Achievements.size()) || m_Achievements[achievement].m_bAchieved) {
        return false; // Invalid achievement ID or already achieved
    }

    // Unlock the achievement
    m_Achievements[achievement].m_bAchieved = true;

    // Call Steam API to unlock the achievement and update stats
    return SteamUserStats()->SetAchievement(m_Achievements[achievement].m_pchAchievementID)
        && SteamUserStats()->StoreStats();
}


void SteamAchievements::Initialize(std::vector<Achievement_t>& achievements, bool reset)
{
    m_Achievements = achievements;

    if (reset) {
        // Reset the achievements
        for (auto& achievement : m_Achievements) {
            SteamUserStats()->ClearAchievement(achievement.m_pchAchievementID);
        }

        // Update the stats
        SteamUserStats()->StoreStats();
    }
}