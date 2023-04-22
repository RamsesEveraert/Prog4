#pragma once
#include "Component.h"

#include <chrono>

namespace dae
{

    class Text;
    class FPSComponent final : public Component
    {
    public:
        FPSComponent();
        ~FPSComponent() = default;

        void Update() override;
        const int GetFPS() const;

    private:
        int m_Fps;
        float m_TimeRunning;
        Text* m_TextComponent;
    };
}