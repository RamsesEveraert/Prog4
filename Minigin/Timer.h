#include "Singleton.h"
#include <chrono>
#include <iostream>

namespace dae
{

    class Timer final : dae::Singleton<Timer> {
    public:
        
        Timer();
        virtual ~Timer() override = default;

        const double getDeltaTimeMs() const; 
        const double msToSeconds(double ms) const;
        
        //stopwatch functions

        void startStopwatch();
        const double stopStopwatch();

        // timer functions

        void startTimer(double durationSeconds);
        bool isTimerFinished() const;

    private:

        std::chrono::high_resolution_clock::time_point stopwatchStart;
        std::chrono::high_resolution_clock::time_point timerStart;
        std::chrono::duration<double> timerDuration;
        std::chrono::duration<double> deltaTime;

        friend void updateDeltaTime(Timer& timer);
    };

    void updateDeltaTime(Timer& timer) {
        static auto previousTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        timer.deltaTime = currentTime - previousTime;
        previousTime = currentTime;
    }

}
