#pragma once
#include "Component.h"

namespace dae
{
    struct Event;
    class Score;
    class GameObject;
    class Text;
    class ScoreDisplayComponent final : public Component
    {
    public:
        ScoreDisplayComponent();
        ~ScoreDisplayComponent() = default;

        void UpdateScoreDisplay(const dae::Event& event);
        void ShowScore(GameObject* gameObject);
        void ShowHighScore(GameObject* gameObject);
        void OnPlayerDied(const dae::Event& event);

    private:
        Score* m_pScore;
        int m_Score, m_HighScore;
        GameObject* m_pOwnerScore;
        Text* m_pTextcomponent;
    };
}


