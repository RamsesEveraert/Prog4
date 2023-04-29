#pragma once
#include "Component.h"


namespace dae
{
    class SpriteAnimation final : public Component
    {
    public:
        SpriteAnimation(float frameTime, int numFrames, bool loop, bool isPlaying = true);
        ~SpriteAnimation() = default;

        virtual void Update() override;

        void SetFrameTime(float frameTime);
        float GetFrameTime() const;

        void SetNumFrames(int numFrames);
        int GetNumFrames() const;

        void SetLoop(bool loop);
        bool GetLoop() const;

        void SetPlaying(bool isPlaying);
        bool IsPlaying() const;

        int GetCurrentFrame() const;

    private:
        float m_FrameTime;
        int m_NumFrames;
        bool m_Loop;
        bool m_IsPlaying;

        int m_CurrentFrame;
        float m_ElapsedTime;
    };

}