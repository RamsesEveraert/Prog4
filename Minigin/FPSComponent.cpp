#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Timer.h"

dae::FPSComponent::FPSComponent(std::weak_ptr<GameObject> pOwner, const std::string& identifier)
    : BaseComponent(pOwner,identifier), m_Fps{ 0 }, m_TimeRunning{ 0.0f }
{
    auto owner = pOwner.lock();
    if (owner->hasComponent<dae::TextComponent>())
    {
        m_TextComponent = owner->GetComponent<dae::TextComponent>();
    }

}

void dae::FPSComponent::Update()
{

    auto& timer = Timer::GetInstance();
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