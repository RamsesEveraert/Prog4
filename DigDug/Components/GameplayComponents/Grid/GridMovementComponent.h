#pragma once
#include <Component.h>
#include "Grid.h"
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
    class Grid;
    class Transform;
	class GridMovementComponent : public Component
	{
    public:
        GridMovementComponent(float speed, Grid* pGrid);
        void Move(const glm::vec2& direction);

        void SetSpeed(float speed);
        const float GetSpeed() const;

        const Grid::Cell& GetCurrentCell() const;

        const Grid::Cell& GetTargetCell() const;

        virtual void Render() override;


    private:

        enum class Direction
        {
            horizontal, vertical, null
        };

        void UpdateCurrentCell(const glm::vec2& currentPosition);
        void UpdateTargetCell(const glm::vec2& normalizedDirection);
        void SetDirectionAxis(glm::vec2& normalizedDirection);
        void SnapPlayerToCell(const glm::vec2& currentPosition, glm::vec2 newPosition, Transform* pPlayerTransform);
        bool IsPlayerInGrid(const glm::vec2& newPosition);

        bool CanMove(const glm::vec2& pookaPosition, const glm::vec2& direction);

        // Grid properties
        Grid* m_pGrid;
        const glm::vec2 m_GridOffset;
        const glm::ivec2 m_GridSize;


        // cell properties
        Grid::Cell m_CurrentCell, m_PreviousCell, m_PreviousTargetCell, m_TargetCell;
        int m_PreviousCellIdx;
        float m_SnapRange;
        const glm::ivec2 m_CellSize;
        std::vector<Grid::Cell> m_Cells;

        // player movement properties
        Direction m_CurrentDirection, m_PreviousDirection;
        float m_Speed;       
	};
}


