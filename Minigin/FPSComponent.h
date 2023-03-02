#pragma once
#include "BaseComponent.h"

#include <chrono>

namespace dae
{

    class TextComponent;
    class FPSComponent final : public BaseComponent
    {
    public:
        FPSComponent(const std::weak_ptr<GameObject>& gameObject);
        ~FPSComponent() = default;

        void Update() override;
        const int GetFPS() const;

    private:
        int m_Fps;
        float m_TimeRunning;
        std::shared_ptr<dae::TextComponent> m_TextComponent;
    };
}