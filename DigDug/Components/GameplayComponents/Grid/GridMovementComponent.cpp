#include "GridMovementComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Grid.h"

#include "Timer.h"

#include "Renderer.h"

// debug purpose

#include <SDL.h>

using namespace dae;

Grid::Cell GridMovementComponent::m_CurrentCell{}, GridMovementComponent::m_PreviousCell{}; // had to be static because every direction button needs acces to the same variable

dae::GridMovementComponent::GridMovementComponent(float speed, Grid* pGrid)
	: m_CurrentDirection{}
	, m_Speed {speed}
	, m_pGrid {pGrid}
	, m_TargetCell{}
	, m_Tolerance{6.f}
    , m_SnappedToCell{}
    , m_PreviousCellIdx{}
{
}

void dae::GridMovementComponent::Move(const glm::vec2& direction)
{
    // Get current and new position of the object
    glm::vec2 currentPosition{ GetOwner()->GetTransform()->GetWorldPosition() };
    glm::vec2 newPosition{ currentPosition + direction * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed };

    // Get grid properties
    const glm::ivec2 cellSize{ static_cast<glm::ivec2>(m_pGrid->GetCellSize()) };
    const glm::ivec2 gridPosition{ static_cast<glm::ivec2>(m_pGrid->GetGridPosition()) };
    const glm::ivec2 gridSize{ static_cast<glm::ivec2>(m_pGrid->GetGridSize()) };

    // Check if the new position is outside the boundaries of the grid
    const SDL_Rect gridBoundaries{ gridPosition.x, gridPosition.y, gridSize.x, gridSize.y };
    if (direction.x < 0 && currentPosition.x <= gridBoundaries.x ||
        direction.x > 0 && currentPosition.x >= gridBoundaries.x + gridBoundaries.w - cellSize.x ||
        direction.y < 0 && currentPosition.y <= gridBoundaries.y ||
        direction.y > 0 && currentPosition.y >= gridBoundaries.y + gridBoundaries.h - cellSize.y)
    {
        return; // Return if the new position is outside the grid
    }

    // Calculate row and column indices based on the new position
    glm::vec2 relativePosition{ newPosition - static_cast<glm::vec2>(gridPosition) };
    int row = static_cast<int>(std::round(relativePosition.y / cellSize.y));
    int col = static_cast<int>(std::round(relativePosition.x / cellSize.x));

    // Move to the next cell if the player is close enough
    MoveToNextCell(direction, currentPosition, newPosition, row, col);

    // Update current cell and previous cell if necessary
    UpdateCurrentAndPreviousCell(row, col);

    // Set new position
    GetOwner()->GetTransform()->SetPosition(newPosition);
}

//void dae::GridMovementComponent::MoveToNextCell(const glm::vec2& direction, const glm::vec2& currentPosition, glm::vec2& newPosition, int row, int col)
//{
//    // Grid properties
//    std::vector<Grid::Cell> cells{ m_pGrid->GetCells() };
//    const glm::vec2 gridPosition{ m_pGrid->GetGridPosition() };
//    const glm::vec2 cellSize{ m_pGrid->GetCellSize() };
//
//
//    // Get current cell
//    int currentCellIdx{ m_pGrid->GetCellIdx(row, col) };
//    Grid::Cell currentCell = cells[currentCellIdx];
//
//    // Check if player is close enough to next cell on y-axis, and move to it if true
//    if (direction.y != 0.0f)
//    {
//        int nextRow{ row + static_cast<int>(std::round(direction.y)) };
//        int nextRowCellIdx{ m_pGrid->GetCellIdx(nextRow, col) };
//
//        if (nextRow >= 0 && nextRow < m_pGrid->GetNrRows() &&
//            std::abs(currentPosition.y - cells[nextRowCellIdx].dstRect.y) < m_Tolerance)
//        {
//            newPosition.y = static_cast<float>(cells[nextRowCellIdx].dstRect.y);
//            newPosition.x = static_cast<float>(col) * cellSize.x + gridPosition.x;
//            // Snap to cell center to avoid snapping issue
//            newPosition.y += cellSize.y * 0.5f;
//        }
//    }
//    // Check if player is close enough to next cell on x-axis, and move to it if true
//    else if (direction.x != 0.0f)
//    {
//        int nextCol = col + static_cast<int>(std::round(direction.x));
//        int nextColCellIdx{ m_pGrid->GetCellIdx(row, nextCol) };
//        if (nextCol >= 0 && nextCol < m_pGrid->GetNrColumns() &&
//            std::abs(currentPosition.x - cells[nextColCellIdx].dstRect.x) < m_Tolerance)
//        {
//            newPosition.x = static_cast<float>(cells[nextColCellIdx].dstRect.x);
//            newPosition.y = static_cast<float>(row) * cellSize.y + gridPosition.y;
//            // Snap to cell center to avoid snapping issue
//            newPosition.x += cellSize.x * 0.5f;
//        }
//    }
//}

void dae::GridMovementComponent::MoveToNextCell(const glm::vec2& direction, const glm::vec2& currentPosition, glm::vec2& newPosition, int row, int col)
{
    // Grid properties
    std::vector<Grid::Cell> cells{ m_pGrid->GetCells() };
    const glm::vec2 gridPosition{ m_pGrid->GetGridPosition() };
    const glm::vec2 cellSize{ m_pGrid->GetCellSize() };

    // Get current cell
    int currentCellIdx{ m_pGrid->GetCellIdx(row, col) };
    Grid::Cell currentCell = cells[currentCellIdx];

    // Check if player is close enough to next cell on y-axis, and move to it if true
    if (direction.y != 0.0f)
    {
        int nextRow{ row + static_cast<int>(std::round(direction.y)) };
        int nextRowCellIdx{ m_pGrid->GetCellIdx(nextRow, col) };

        if (nextRow >= 0 && nextRow < m_pGrid->GetNrRows() &&
            std::abs(currentPosition.y - cells[nextRowCellIdx].dstRect.y) < m_Tolerance)
        {
            // Snap to cell if moving towards a new cell
            if (!m_SnappedToCell || m_PreviousCellIdx != nextRowCellIdx)
            {
                newPosition.y = static_cast<float>(cells[nextRowCellIdx].dstRect.y);
                newPosition.x = static_cast<float>(col) * cellSize.x + gridPosition.x;
                // Snap to cell center to avoid snapping issue
                newPosition.y += cellSize.y * 0.5f;

                // Remember the cell that we snapped to
                m_PreviousCellIdx = nextRowCellIdx;
                m_SnappedToCell = true;
            }
        }
        else
        {
            m_SnappedToCell = false;
        }
    }
    // Check if player is close enough to next cell on x-axis, and move to it if true
    else if (direction.x != 0.0f)
    {
        int nextCol = col + static_cast<int>(std::round(direction.x));
        int nextColCellIdx{ m_pGrid->GetCellIdx(row, nextCol) };
        if (nextCol >= 0 && nextCol < m_pGrid->GetNrColumns() &&
            std::abs(currentPosition.x - cells[nextColCellIdx].dstRect.x) < m_Tolerance)
        {
            // Snap to cell if moving towards a new cell
            if (!m_SnappedToCell || m_PreviousCellIdx != nextColCellIdx)
            {
                newPosition.x = static_cast<float>(cells[nextColCellIdx].dstRect.x);
                newPosition.y = static_cast<float>(row) * cellSize.y + gridPosition.y;
                // Snap to cell center to avoid snapping issue
                newPosition.x += cellSize.x * 0.5f;
                // Remember the cell that we snapped to
                m_PreviousCellIdx = nextColCellIdx;
                m_SnappedToCell = true;
            }
        }
        else
        {
            m_SnappedToCell = false;
        }
    }
}




void dae::GridMovementComponent::UpdateCurrentAndPreviousCell(int row, int col)
{
    // Get current cell
    Grid::Cell currentCell = m_pGrid->GetCells()[m_pGrid->GetCellIdx(row, col)];

    // Update current cell and previous cell if necessary
    if (row != m_CurrentCell.row || col != m_CurrentCell.col)
    {
        m_PreviousCell = m_CurrentCell;
        m_CurrentCell = { row, col, currentCell.dstRect };
    }
}

void dae::GridMovementComponent::Render()
{

    SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green color
    SDL_RenderDrawRect(renderer, &m_CurrentCell.dstRect);

}
