#include "MoveCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* pGameObject, float speed, const glm::vec2& direction)
    : Command(pGameObject)
    , m_pGameObject { pGameObject }
    , m_OldPosition{ pGameObject->GetTransform()->GetLocalPosition() }
    , m_Direction{ direction }
    , m_Speed{ speed }
{

};

void dae::MoveCommand::SetDirection(const glm::vec2& direction)
{
    m_Direction = direction;
}

void MoveCommand::Execute()
{
    if (m_pGameObject == nullptr) return;

    m_OldPosition = m_pGameObject->GetTransform()->GetLocalPosition();
    glm::vec2 newPosition = m_OldPosition + m_Direction * Timer::GetInstance().getDeltaTimeSec() * m_Speed;

    m_pGameObject->GetTransform()->SetPosition(newPosition);

    //std::cout << "Pos: [" << newPosition.x << ", " << newPosition.y << "] \n";
}
