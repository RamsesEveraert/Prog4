#pragma once
#include "Component.h"

namespace dae
{
    struct Event;
    class Health;
    class GameObject;
    class Text;
    class LivesDisplayComponent final : public Component
    {
    public:
        LivesDisplayComponent();
        ~LivesDisplayComponent();

        void OnPlayerDied(const dae::Event& event);

        void UpdateLivesDisplay(const dae::Event& event);

        void SetOwnerLives(GameObject* gameObject);

    private:
        Health* m_pHealth;
        int m_Lives;
        GameObject* m_pOwnerLives;
        Text* m_pTextcomponent;
    };
}


