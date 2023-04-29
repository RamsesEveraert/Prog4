#include "SpriteAnimation.h"
#include "Timer.h"

dae::SpriteAnimation::SpriteAnimation(float frameTime, int numFrames, bool loop, bool isPlaying)
    : m_FrameTime{ frameTime }, m_NumFrames{ numFrames }, m_Loop{ loop }, m_IsPlaying{ isPlaying }
    , m_CurrentFrame{}, m_ElapsedTime{}
{}

void dae::SpriteAnimation::Update()
{
    if (m_IsPlaying)
    {
        m_ElapsedTime += TimeManager::GetInstance().GetDeltaTimeSec();
        if (m_ElapsedTime >= m_FrameTime)
        {
            m_CurrentFrame++;
            if (m_CurrentFrame >= m_NumFrames)
            {
                if (m_Loop)
                {
                    m_CurrentFrame = 0;
                }
                else
                {
                    m_CurrentFrame = m_NumFrames - 1;
                    m_IsPlaying = false;
                }
            }
            m_ElapsedTime = 0.f; 

        }
    }
}

void dae::SpriteAnimation::SetFrameTime(float frameTime)
{
    m_FrameTime = frameTime;
}

float dae::SpriteAnimation::GetFrameTime() const
{
    return m_FrameTime;
}

void dae::SpriteAnimation::SetNumFrames(int numFrames)
{
    m_NumFrames = numFrames;
}

int dae::SpriteAnimation::GetNumFrames() const
{
    return m_NumFrames;
}

void dae::SpriteAnimation::SetLoop(bool loop)
{
    m_Loop = loop;
}

bool dae::SpriteAnimation::GetLoop() const
{
    return m_Loop;
}

void dae::SpriteAnimation::SetPlaying(bool isPlaying)
{
    m_IsPlaying = isPlaying;
}

bool dae::SpriteAnimation::IsPlaying() const
{
    return m_IsPlaying;
}

int dae::SpriteAnimation::GetCurrentFrame() const
{
    return m_CurrentFrame;
}

