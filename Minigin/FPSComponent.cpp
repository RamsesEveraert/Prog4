#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Timer.h"

dae::FPSComponent::FPSComponent(const std::weak_ptr<GameObject>& gameObject)
    : BaseComponent(gameObject), m_Fps{ 0 }, m_TimeRunning{ 0.0f }
{
	
}

void dae::FPSComponent::Update()
{
    auto& timer = Timer::GetInstance();

    m_TimeRunning += timer.msToSeconds(timer.getDeltaTimeMs());
    const float timeLimit{1.f};

    if (m_TimeRunning >= timeLimit) // display fps every sec
    {
        m_Fps = static_cast<int>(1000 / timer.getDeltaTimeMs());
        if (m_GameObject.lock()->hasComponent<dae::TextComponent>())
        {
            m_GameObject.lock()->GetComponent<dae::TextComponent>()->SetText("FPS: " + std::to_string(m_Fps));
        }

        m_TimeRunning -= timeLimit;
    }

   
}

const int dae::FPSComponent::GetFPS() const
{
    return m_Fps;
}
