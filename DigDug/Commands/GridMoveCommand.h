#pragma once
#include "StickCommand.h"

namespace dae
{
    class GameObject;
    class Transform;
    class GridMovementComponent;
    class Grid;
	class GridMoveCommand : public StickCommand
	{
    public:
        GridMoveCommand(GameObject* go, float speed, const glm::vec2& direction, Grid* pGrid);
        ~GridMoveCommand() = default;

        virtual void Execute() override;
        virtual void SetDirection(const glm::vec2& direction);
        virtual void SetSpeed(float speed);

    private:
        GridMovementComponent* m_pGridMovementComponent;
        glm::vec2 m_Direction;
	};

}