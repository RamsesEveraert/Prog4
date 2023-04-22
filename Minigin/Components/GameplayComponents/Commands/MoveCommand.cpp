#include "MoveCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"
#include "MovementComponent.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* go, float speed, const glm::vec2& direction)
    : m_Direction{ direction }
{
    m_pMovementComponent = go->GetComponent<MovementComponent>();
    m_pMovementComponent->SetSpeed(speed);
}

void MoveCommand::Execute()
{
    m_pMovementComponent->Move(m_Direction);
}
