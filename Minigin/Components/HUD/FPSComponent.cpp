#include "FPSComponent.h"

#include "GameObject.h"
#include "Text.h"
#include "Timer.h"

#include "Texture.h"

dae::FPSComponent::FPSComponent()
    :  m_Fps{ }
    , m_TimeRunning{ }
    , m_pTextComponent{}
    , m_pTexture{}
{

}

void dae::FPSComponent::Update()
{

    if (!m_pTextComponent) m_pTextComponent = GetOwner()->AddComponent<Text>();

    auto& timeManager = TimeManager::GetInstance();
    m_TimeRunning += timeManager.GetDeltaTimeSec();
    const float timeLimit = 1.f;

    if (m_TimeRunning >= timeLimit) // display fps every sec
    {
        m_Fps = static_cast<int>(1 / timeManager.GetDeltaTimeSec());

        if (m_pTextComponent)
        {
            m_pTextComponent->SetText("FPS: " + std::to_string(m_Fps));
        }

        m_TimeRunning -= timeLimit;
    }

}

const int dae::FPSComponent::GetFPS() const
{
    return m_Fps;
}

void dae::FPSComponent::SetColor(SDL_Color color)
{
    if (!m_pTextComponent) m_pTextComponent = GetOwner()->AddComponent<Text>();
    m_pTextComponent->SetTextColor(color);
}
