#include "MoveCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* pGameObject, float speed, const glm::vec3& direction)
    : m_pGameObject {pGameObject}
    , m_OldPosition(pGameObject->GetTransform()->GetLocalPosition())
    , m_Direction(direction) 
    , m_Speed{speed}
    , m_pTransform{ pGameObject->GetTransform() }
{

};

void MoveCommand::Execute()
{
   /* GameObject* pGameObject = GetGameObject();*/

    if (m_pGameObject == nullptr) return;

    m_OldPosition = m_pGameObject->GetTransform()->GetLocalPosition();
    glm::vec3 newPosition = m_OldPosition + m_Direction * Timer::GetInstance().getDeltaTimeSec() * m_Speed;

    m_pTransform->SetPosition(newPosition);

   // std::cout << "Pos: [" << newPosition.x << ", " << newPosition.y << "] \n";
}
