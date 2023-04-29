#pragma once
#include "Command.h"

namespace dae
{
    class GameObject;
    class Transform;
    class GridMovementComponent;
    class Grid;
	class GridMoveCommand : public Command
	{
    public:
        GridMoveCommand(GameObject* go, float speed, const glm::vec2& direction, Grid* pGrid);
        ~GridMoveCommand() = default;

        virtual void Execute() override;

    private:
        GridMovementComponent* m_pGridMovementComponent;
        glm::vec2 m_Direction;
	};

}