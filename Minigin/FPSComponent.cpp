#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Timer.h"

dae::FPSComponent::FPSComponent(const std::weak_ptr<GameObject>& gameObject)
    : BaseComponent(gameObject), m_Fps{ 0 }, m_TimeRunning{ 0.0f }
{
    
    if (gameObject.lock()->HasComponent<dae::TextComponent>())
    {
        m_TextComponent = gameObject.lock()->GetComponent<dae::TextComponent>();
    }

}

void dae::FPSComponent::Update()
{

    auto& timer =Timer::GetInstance();
    float dt = timer.getDeltaTimeMs();
    
    m_TimeRunning += timer.msToSeconds(dt);
    const float timeLimit = 1.f;

    if (m_TimeRunning >= timeLimit) // display fps every sec
    {
        m_Fps = static_cast<int>(1000 / timer.getDeltaTimeMs());
       
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
