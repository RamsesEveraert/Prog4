#include "Timer.h"

dae::Timer::Timer()
    : deltaTime{ 0.0 }, timerDuration{ 0.0 }
{

}

void dae::Timer::updateDeltaTime(Timer& timer)
{
    static auto previousTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    timer.deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}

const float dae::Timer::getDeltaTimeMs() const
{
	return std::chrono::duration<float, std::milli>(deltaTime).count();
}

const float dae::Timer::msToSeconds(float ms) const
{
	return ms / 1000.0f;
}

void dae::Timer::startStopwatch()
{
	stopwatchStart = std::chrono::high_resolution_clock::now();
}

const float dae::Timer::stopStopwatch()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - stopwatchStart;
    return std::chrono::duration<float>(elapsed).count();
}

void dae::Timer::startTimer(float durationSeconds)
{
    timerStart = std::chrono::high_resolution_clock::now();
    timerDuration = std::chrono::duration<float>(durationSeconds);
}

bool dae::Timer::isTimerFinished() const
{
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - timerStart;
    return elapsed >= timerDuration;
}
