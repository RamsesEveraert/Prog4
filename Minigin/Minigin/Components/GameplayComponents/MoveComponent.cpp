#include "MoveComponent.h"

#include "GameObject.h"
#include "Transform.h"

#include "Timer.h"


void dae::MovementComponent::Move(const glm::vec2& direction)
{
    glm::vec2 currentPosition = GetOwner()->GetTransform()->GetLocalPosition();
    glm::vec2 newPosition = currentPosition + direction * Timer::GetInstance().getDeltaTimeSec() * m_Speed;
    GetOwner()->GetTransform()->SetPosition(newPosition);
}

void dae::MovementComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}

const float dae::MovementComponent::GetSpeed() const
{
    return m_Speed;
}
