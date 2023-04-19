#pragma once
#include "BaseComponent.h"

namespace dae
{
    struct Event;
    class Score;
    class GameObject;
    class TextComponent;
    class ScoreDisplayComponent final : public BaseComponent
    {
    public:
        ScoreDisplayComponent();
        ~ScoreDisplayComponent();

        void UpdateScoreDisplay(const dae::Event& event);
        void SetOwnerScore(GameObject* gameObject);
        void OnPlayerDied(const dae::Event& event);

    private:
        Score* m_pScore;
        int m_Score;
        GameObject* m_pOwnerScore;
        TextComponent* m_pTextcomponent;
    };
}


