#pragma once
#include "Command.h"


namespace dae
{
    class GameObject;
    class Transform;
    class MoveCommand final: public Command
    {
    public:
        MoveCommand(GameObject* pGameObject, float speed ,const glm::vec2& direction);
        ~MoveCommand() = default;

       virtual void SetDirection(const glm::vec2& direction) override;

       virtual void Execute() override;

    private:
        GameObject* m_pGameObject;
        glm::vec2 m_OldPosition;
        glm::vec2 m_Direction;
        const float m_Speed;

    };
}