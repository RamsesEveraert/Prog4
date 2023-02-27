#include "Time.h"
#include "Timer.h"

dae::Timer::Timer()
: deltaTime(0.0) 
{

}

const double dae::Timer::getDeltaTimeMs() const
{
	return std::chrono::duration<double, std::milli>(deltaTime).count();
}

const double dae::Timer::msToSeconds(double ms) const
{
	return ms / 1000.0;
}

void dae::Timer::startStopwatch()
{
	stopwatchStart = std::chrono::high_resolution_clock::now();
}

const double dae::Timer::stopStopwatch()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - stopwatchStart;
    return std::chrono::duration<double>(elapsed).count();
}

void dae::Timer::startTimer(double durationSeconds)
{
    timerStart = std::chrono::high_resolution_clock::now();
    timerDuration = std::chrono::duration<double>(durationSeconds);
}

bool dae::Timer::isTimerFinished() const
{
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - timerStart;
    return elapsed >= timerDuration;
}
