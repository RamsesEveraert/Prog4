#pragma once
#include <Component.h>
#include "Grid.h"
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
    class Grid;
	class GridMovementComponent : public Component
	{
    public:
        GridMovementComponent(float speed, Grid* pGrid);
        void Move(const glm::vec2& direction);
        void SetSpeed(float speed);
        const float GetSpeed() const;
        void SetDirection(const glm::vec2& direction);
        virtual void Render() override;

    private:

        void MoveToNextCell(const glm::vec2& direction, const glm::vec2& currentPosition, glm::vec2& newPosition, int row, int col);
        void UpdateCurrentAndPreviousCell(int row, int col);



        static Grid::Cell m_CurrentCell, m_PreviousCell;
        Grid::Cell m_TargetCell;

        int m_PreviousCellIdx;

        glm::vec2 m_CurrentDirection;
        float m_Speed;
        Grid* m_pGrid;
        float m_Tolerance;
        bool m_SnappedToCell;
	};
}


