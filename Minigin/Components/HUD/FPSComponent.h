#pragma once
#include "Component.h"

#include <chrono>
#include <SDL.h>

namespace dae
{

    class Text;
    class Texture;
    class FPSComponent final : public Component
    {
    public:
        FPSComponent();
        ~FPSComponent() = default;

        void Update() override;
        const int GetFPS() const;

        void SetColor(SDL_Color color);

    private:
        int m_Fps;
        float m_TimeRunning;
        Text* m_pTextComponent;
        Texture* m_pTexture;
    };
}