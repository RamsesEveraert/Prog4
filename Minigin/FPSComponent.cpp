#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(const std::weak_ptr<GameObject>& gameObject)
	: BaseComponent(gameObject), m_frames{ 0 }, m_fps{ 0 }
{
	m_startTime = std::chrono::high_resolution_clock::now();
}

void dae::FPSComponent::Update()
{
    ++m_frames;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count();

    if (elapsedTime >= 1000)
    {
        m_fps = m_frames;
        m_frames = 0;
        m_startTime = currentTime;
    }
}

const int dae::FPSComponent::getFPS() const
{
    return m_fps;
}
