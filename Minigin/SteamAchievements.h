#pragma once

#include "Singleton.h"
#include <vector>
#include <string>


#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

namespace dae
{

    struct Achievement_t
    {
        int m_eAchievementID;
        const char* m_pchAchievementID;
        char m_rgchName[128];
        char m_rgchDescription[256];
        bool m_bAchieved;
        int m_iIconImage;
    };

    // Defining our achievements
    enum EAchievements
    {
        ACH_WIN_ONE_GAME = 0,
        ACH_WIN_100_GAMES = 1,
        ACH_TRAVEL_FAR_ACCUM = 2,
        ACH_TRAVEL_FAR_SINGLE = 3,
    };

    class SteamAchievements : public Singleton<SteamAchievements>
    {
    public:
        bool SetAchievement(const EAchievements& achievement);
        void Initialize(std::vector<Achievement_t>& achievements, bool reset);

    private:
        std::vector<Achievement_t> m_Achievements; // Achievements data

    };
}