#pragma once
#include "BaseComponent.h"

#include <chrono>

namespace dae
{

    class TextComponent;
    class FPSComponent final : public BaseComponent
    {
    public:
        FPSComponent();
        ~FPSComponent() = default;

        void Update() override;
        const int GetFPS() const;

    private:
        int m_Fps;
        float m_TimeRunning;
        TextComponent* m_TextComponent;
    };
}