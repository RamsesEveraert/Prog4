#include "MoveStickCommand.h"
#include "GameObject.h"

#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"
#include "MovementComponent.h"

using namespace dae;
  

dae::MoveStickCommand::MoveStickCommand(GameObject* go, float speed, const glm::vec2& direction)
    : m_Direction{ direction }
    , m_GameObject {go}
    , m_Speed{ speed }
{
    m_pMovementComponent = m_GameObject->AddComponent<MovementComponent>(speed);
}

void dae::MoveStickCommand::Execute() 
{
    m_pMovementComponent->Move(m_Direction);
}


void dae::MoveStickCommand::SetDirection(const glm::vec2& direction)
{
    m_Direction = direction;
}

void dae::MoveStickCommand::SetSpeed(float speed)
{
    m_pMovementComponent->SetSpeed(speed);
}
