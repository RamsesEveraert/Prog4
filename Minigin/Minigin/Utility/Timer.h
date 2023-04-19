#include "Singleton.h"
#include <chrono>
#include <iostream>

namespace dae
{

    class Timer final : public Singleton<Timer> {
    public:
        
        
        virtual ~Timer() override = default;

        // dt functions

        const float getDeltaTimeMs() const; 
        const float getDeltaTimeSec() const; 
        const float msToSeconds(float ms) const;
       
        void updateDeltaTime(Timer& timer);
        
        //stopwatch functions

        void startStopwatch();
        const float stopStopwatch();

        // timer functions

        void startTimer(float durationSeconds);
        bool isTimerFinished() const;

    private:
        friend class Singleton<Timer>;
        Timer();

        


        std::chrono::high_resolution_clock::time_point stopwatchStart;
        std::chrono::high_resolution_clock::time_point timerStart;
        std::chrono::duration<float> timerDuration;
        std::chrono::duration<float> deltaTime;

       
    };

    

}
