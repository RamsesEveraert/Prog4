#include "MoveCommand.h"
#include "GameObject.h"
#include "Timer.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* pGameObject, float speed, const glm::vec3& direction)
    : Command(pGameObject)
    , m_OldPosition(pGameObject->GetLocalPosition())
    , m_Direction(direction) 
    , m_Speed{speed}
{

};

void MoveCommand::Execute()
{
    GameObject* pGameObject = GetGameObject();

    if (pGameObject == nullptr) return;

    m_OldPosition = pGameObject->GetLocalPosition();
    glm::vec3 newPosition = m_OldPosition + m_Direction * Timer::GetInstance().getDeltaTimeSec() * m_Speed;

    pGameObject->SetPosition(newPosition);
}

void MoveCommand::Undo()
{
    GameObject* pGameObject = GetGameObject();

    if (pGameObject == nullptr) return;

    pGameObject->SetPosition(m_OldPosition);
}