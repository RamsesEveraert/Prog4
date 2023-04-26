
#include "Timer.h"

dae::Stopwatch::Stopwatch()
{
}

void dae::Stopwatch::Start()
{
    m_StartTime = std::chrono::high_resolution_clock::now();
}

float dae::Stopwatch::Stop()const
{
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<float>(endTime - m_StartTime);
    return elapsed.count();
}

dae::Timer::Timer(float durationSeconds)
    : m_Duration(durationSeconds)
{
}

void dae::Timer::Update()
{
    m_Stopwatch.Start();
}

bool dae::Timer::IsFinished() const
{
    return m_Stopwatch.Stop() >= m_Duration.count();
}

dae:: TimeManager::TimeManager()
{
    m_PreviousTime = std::chrono::high_resolution_clock::now();
}

float dae::TimeManager::GetDeltaTimeMs() const
{
    return std::chrono::duration<float, std::milli>(m_DeltaTime).count();
}

float dae::TimeManager::GetDeltaTimeSec() const
{
    return std::chrono::duration<float, std::milli>(m_DeltaTime).count() / 1000.f;
}

void dae::TimeManager::Update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    m_DeltaTime = currentTime - m_PreviousTime;
    m_PreviousTime = currentTime;
}
