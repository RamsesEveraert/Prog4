#pragma once
#include "StickCommand.h"

namespace dae
{
    class GameObject;
    class Transform;
    class MovementComponent;
    class MoveStickCommand final : public StickCommand
    {
    public:
        MoveStickCommand(GameObject* go, float speed, const glm::vec2& direction);
        ~MoveStickCommand() = default;

        virtual void SetDirection(const glm::vec2& direction) override;
        virtual void SetSpeed(float speed) override;

        virtual void Execute() override;

    private:
        MovementComponent* m_pMovementComponent;
        glm::vec2 m_Direction;
        float m_Speed;
    };
}

  