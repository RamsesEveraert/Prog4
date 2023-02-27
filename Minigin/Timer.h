#pragma once
#pragma once
#include <chrono>
#include "Singleton.h"

class Timer final : public dae::Singleton<Timer>
{

    //TODO

public:
    void Start();
    void Update();

private:
    float m_lastTime{ 0.f };
    float m_currentTime{ 0.f };
    float m_deltaTime{ 0.f };
    std::chrono::high_resolution_clock::time_point m_previousTime;
    std::chrono::high_resolution_clock::time_point m_beginTime;
};