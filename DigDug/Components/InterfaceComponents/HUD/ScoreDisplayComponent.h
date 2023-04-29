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
        void SetOwnerScore(GameObject* gameObject);
        void OnPlayerDied(const dae::Event& event);

    private:
        Score* m_pScore;
        int m_Score;
        GameObject* m_pOwnerScore;
        Text* m_pTextcomponent;
    };
}


