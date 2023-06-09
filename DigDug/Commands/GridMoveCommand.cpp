#include "GridMoveCommand.h"
#include "GameObject.h"
#include "Transform.h"
#include "GridMovementComponent.h"
#include "Grid.h"

using namespace dae;



dae::GridMoveCommand::GridMoveCommand(GameObject* go, float speed, const glm::vec2& direction, Grid* pGrid)
    : m_Direction{ direction }
    , m_pGridMovementComponent { go->GetComponent<GridMovementComponent>() }
{
    if(m_pGridMovementComponent == nullptr) m_pGridMovementComponent = go->AddComponent<GridMovementComponent>(speed, pGrid);
}

void dae::GridMoveCommand::Execute()
{
    m_pGridMovementComponent->Move(m_Direction);
}

void dae::GridMoveCommand::SetDirection(const glm::vec2& direction)
{
    m_Direction = direction;
}

void dae::GridMoveCommand::SetSpeed(float speed)
{
    m_pGridMovementComponent->SetSpeed(speed);
}
