#pragma once
#include "Singleton.h"
#include <chrono>
 namespace dae
        {

            //stop watch

            class Stopwatch final : public Singleton<Stopwatch>
            {
            public:
                Stopwatch();

                void Start();
                float Stop() const;

            private:
                friend class Singleton<Stopwatch>;
                std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
            };

            // timer

            class Timer final : public Singleton<Timer>
            {
            public:
                Timer(float durationSeconds);

                void Update();
                bool IsFinished() const;

            private:
                friend class Singleton<Timer>;
                Stopwatch m_Stopwatch;
                std::chrono::duration<float> m_Duration;
            };

            //TimeManager for delta tilme

            class TimeManager final : public Singleton<TimeManager>
            {
            public:
                TimeManager();

                float GetDeltaTimeMs() const;
                float GetDeltaTimeSec() const;
                void Update();

            private:
                friend class Singleton<TimeManager>;
                std::chrono::time_point<std::chrono::steady_clock> m_PreviousTime;
                std::chrono::duration<float> m_DeltaTime;
            };
        }

