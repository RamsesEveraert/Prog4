#pragma once
#include "BaseComponent.h"

namespace dae
{
    struct Event;
    class Health;
    class GameObject;
    class TextComponent;
    class LivesDisplayComponent final : public BaseComponent
    {
    public:
        LivesDisplayComponent();
        void OnPlayerDied(const dae::Event& event);
        void UpdateLivesDisplay(const dae::Event& event);

        void SetOwnerLives(GameObject* gameObject);

    private:
        Health* m_pHealth;
        int m_Lives;
        GameObject* m_pOwnerLives;
        TextComponent* m_pTextcomponent;
    };
}


