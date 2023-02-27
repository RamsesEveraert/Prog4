#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Timer.h"

dae::FPSComponent::FPSComponent(const std::weak_ptr<GameObject>& gameObject)
    : BaseComponent(gameObject), m_fps{ 0 }, m_timeRunning{ 0.0f }
{
	
}

void dae::FPSComponent::Update()
{
    auto& timer = Timer::GetInstance();

    m_timeRunning += timer.msToSeconds(timer.getDeltaTimeMs());
    const float timeLimit{1.f};

    if (m_timeRunning >= timeLimit)
    {
        m_fps = static_cast<int>(1000 / timer.getDeltaTimeMs());
        if (m_gameObject.lock()->hasComponent<dae::TextComponent>())
        {
            m_gameObject.lock()->GetComponent<dae::TextComponent>()->SetText("FPS: " + std::to_string(m_fps));
        }

        m_timeRunning -= timeLimit;
    }

   
}

const int dae::FPSComponent::getFPS() const
{
    return m_fps;
}
