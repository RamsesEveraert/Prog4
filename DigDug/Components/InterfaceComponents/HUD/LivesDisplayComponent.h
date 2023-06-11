#pragma once
#include "Component.h"

namespace dae
{
    struct Event;
    class Health;
    class GameObject;
    class Sprite;
    class LivesDisplayComponent final : public Component
    {
    public:
        LivesDisplayComponent(GameObject* player, bool isPlayer1);
        ~LivesDisplayComponent() = default;

        void UpdateLivesDisplay(const dae::Event& event);

        void InitializeLivesSprites();

    private:
        Health* m_pHealth;
        int m_Lives;
        bool m_IsPlayer1;
        GameObject* m_pOwnerLives;
        Sprite* m_pSprite;
    };
}


