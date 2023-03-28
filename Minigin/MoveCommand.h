#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
    class GameObject;
    class Transform;
    class MoveCommand : public Command
    {
    public:
        MoveCommand(GameObject* pGameObject, float speed ,const glm::vec3& direction);

       virtual void Execute() override;
       virtual void Undo() override;

    private:
        glm::vec3 m_OldPosition;
        glm::vec3 m_Direction;
        float m_Speed;

    };
}