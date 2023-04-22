#include "FPSComponent.h"

#include "GameObject.h"
#include "Text.h"
#include "Timer.h"

dae::FPSComponent::FPSComponent()
    :  m_Fps{ 0 }
    , m_TimeRunning{ 0.0f }
{

}

void dae::FPSComponent::Update()
{

    if (!m_TextComponent)
    {
        m_TextComponent = GetOwner()->GetComponent<Text>();

        if (!m_TextComponent)
        {
            std::cout << "No TextComponent found! \n";
            return;
        }
    }

    auto& timer = Timer::GetInstance();
    m_TimeRunning += timer.getDeltaTimeSec();
    const float timeLimit = 1.f;

    if (m_TimeRunning >= timeLimit) // display fps every sec
    {
        m_Fps = static_cast<int>(1 / timer.getDeltaTimeSec());

        if (m_TextComponent)
        {
            m_TextComponent->SetText("FPS: " + std::to_string(m_Fps));
        }

        m_TimeRunning -= timeLimit;
    }


}


const int dae::FPSComponent::GetFPS() const
{
    return m_Fps;
}