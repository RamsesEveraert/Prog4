#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
    class GameObject;
    class Transform;
    class MoveCommand final: public Command
    {
    public:
        MoveCommand(GameObject* pGameObject, float speed ,const glm::vec3& direction);
        ~MoveCommand() = default;

       virtual void Execute() override;

    private:
        glm::vec3 m_OldPosition;
        glm::vec3 m_Direction;
        float m_Speed;

        Transform* m_pTransform;
        GameObject* m_pGameObject;
    };
}