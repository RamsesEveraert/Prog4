#pragma once
#include "Command.h"


namespace dae
{
    class GameObject;
    class Transform;
    class MovementComponent;
    class MoveCommand final: public Command
    {
    public:
        MoveCommand(GameObject* go, float speed, const glm::vec2& direction);
        ~MoveCommand() = default;

       virtual void Execute() override;

    private:
        MovementComponent* m_pMovementComponent;
        glm::vec2 m_Direction;

    };
}