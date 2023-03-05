#pragma once
#include "BaseComponent.h"

#include <chrono>

namespace dae
{

    class TextComponent;
    class FPSComponent final : public BaseComponent
    {
    public:
        FPSComponent(std::weak_ptr<GameObject> owner, const std::string& identifier = "");
        ~FPSComponent() = default;

        void Update() override;
        const int GetFPS() const;

    private:
        int m_Fps;
        float m_TimeRunning;
        std::shared_ptr<dae::TextComponent> m_TextComponent;
    };
}