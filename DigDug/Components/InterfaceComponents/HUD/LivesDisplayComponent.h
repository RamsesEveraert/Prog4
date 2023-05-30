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
        LivesDisplayComponent(GameObject* player);
        ~LivesDisplayComponent() = default;

        void UpdateLivesDisplay(const dae::Event& event);

        void InitializeLivesSprites();

    private:
        Health* m_pHealth;
        int m_Lives;
        GameObject* m_pOwnerLives;
        Sprite* m_pSprite;
    };
}


