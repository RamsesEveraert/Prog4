#include "GridMovementComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Grid.h"
#include "Sprite.h"
#include "GameObject.h"

#include "Timer.h"
#include "Renderer.h"
#include "EventQueue.h"

#include "Event.h"

#include <SDL.h>

using namespace dae;

Grid::Cell GridMovementComponent::m_CurrentCell{}; // had to be static because every direction button needs acces to the same variable
Grid::Cell GridMovementComponent::m_TargetCell{};
Grid::Cell GridMovementComponent::m_PreviousCell{};
Grid::Cell GridMovementComponent::m_PreviousTargetCell{};

GridMovementComponent::Direction GridMovementComponent::m_CurrentDirection = Direction::null;
GridMovementComponent::Direction GridMovementComponent::m_PreviousDirection = Direction::null;


dae::GridMovementComponent::GridMovementComponent(float speed, Grid* pGrid)
    : m_Speed{ speed }
    , m_pGrid{ pGrid }
    , m_PreviousCellIdx{}
    , m_SnapRange {1.f}
    , m_CellSize{ static_cast<glm::ivec2>(pGrid->GetCellSize()) }
    , m_GridOffset{ static_cast<glm::ivec2>(pGrid->GetGridPosition()) }
    , m_GridSize{ static_cast<glm::ivec2>(pGrid->GetGridSize()) }
    , m_Cells{ pGrid->GetCells() }
{
}

void dae::GridMovementComponent::Move(const glm::vec2& direction)
{
    // Get the current center position of the sprite
    Transform* pPlayerTransform{ GetOwner()->GetTransform() };
    const glm::vec2 currentPosition{ pPlayerTransform->GetWorldPosition() };
    const glm::vec2 playerCenter{ GetOwner()->GetSpriteCenterPoint()};

    // Notify Move Event
    {
        Event moveEvent{ "PlayerMoved",{GetOwner()->GetObjectName(), playerCenter}};
        EventQueue::GetInstance().Dispatch(moveEvent);
    }

    // Find the current and target cells
    UpdateCurrentCell(playerCenter);
    UpdateTargetCell(direction);

    // Send event current cell as digged
    if (m_PreviousCell.row != m_CurrentCell.row || m_PreviousCell.col != m_CurrentCell.col)
    {
        Event digEvent{ "DiggedCell", {m_CurrentCell} };
        EventQueue::GetInstance().Dispatch(digEvent);
    }

    // Normalize direction
    glm::vec2 normalizedDirection{ glm::normalize(direction) };
    //std::cout << "normalized direction: { " << std::to_string(normalizedDirection.x) << ", " << std::to_string(normalizedDirection.y) << "} \n";

    // Set the Direction axis
    SetDirectionAxis(normalizedDirection);

    // Check if player wants to change direction and if it's possible
    if (m_CurrentDirection != m_PreviousDirection && (abs(currentPosition.x - m_TargetCell.dstRect.x) > m_SnapRange || abs(currentPosition.y - m_TargetCell.dstRect.y) > m_SnapRange))
    {
        // Update direction based on the previous direction
        if (m_PreviousDirection == Direction::horizontal)
        {
            normalizedDirection.x = glm::sign(m_PreviousTargetCell.dstRect.x - currentPosition.x);
            normalizedDirection.y = 0.0f;
        }
        else
        {
            normalizedDirection.x = 0.0f;
            normalizedDirection.y = glm::sign(m_PreviousTargetCell.dstRect.y - currentPosition.y);
        }

        // Set the Direction axis
        SetDirectionAxis(normalizedDirection);

        // Update the target cell
        UpdateTargetCell(normalizedDirection);
    }

    // Calculate the new position of the sprite based on the given direction
    glm::vec2 newPosition{ currentPosition + (normalizedDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed) };

    // Keep player in grid bounds
    if (IsPlayerInGrid(newPosition))
    {
        SnapPlayerToCell(currentPosition, newPosition, pPlayerTransform);
    }

    m_PreviousDirection = m_CurrentDirection;
    m_PreviousTargetCell = m_TargetCell;
    m_PreviousCell = m_CurrentCell;
}


void dae::GridMovementComponent::UpdateCurrentCell(const glm::vec2& currentPosition)
{
    const int currentCellIdx = m_pGrid->GetCellIdxFromPosition(currentPosition);
    m_CurrentCell = m_Cells[currentCellIdx];   
}

void dae::GridMovementComponent::UpdateTargetCell(const glm::vec2& normalizedDirection)
{
    if (m_CurrentDirection == Direction::horizontal)
    {
        int nextColNr{ m_CurrentCell.col + static_cast<int>(std::round(normalizedDirection.x)) };
        int nextCol{ glm::clamp(nextColNr, 0, m_pGrid->GetNrColumns() - 1) }; // Clamp the next column index
        int nextCellIdx{ m_pGrid->GetCellIdx(m_CurrentCell.row, nextCol) };
        m_TargetCell = m_Cells[nextCellIdx];
    }
    else 
    {
        int nextRowNr{ m_CurrentCell.row + static_cast<int>(std::round(normalizedDirection.y)) };
        int nextRow{ glm::clamp(nextRowNr, 0, m_pGrid->GetNrRows() - 1) }; // Clamp the next row index
        int nextCellIdx{ m_pGrid->GetCellIdx(nextRow, m_CurrentCell.col) };
        m_TargetCell = m_Cells[nextCellIdx];
    }
}


void dae::GridMovementComponent::SetDirectionAxis(glm::vec2& normalizedDirection)
{
    // Check the dominant movement
    const float absX = std::abs(normalizedDirection.x);
    const float absY = std::abs(normalizedDirection.y);

    if (absX > absY)
    {
        // Horizontal movement is dominant
        m_CurrentDirection = Direction::horizontal;
        normalizedDirection.x = glm::sign(normalizedDirection.x);
        normalizedDirection.y = 0;
    }
    else
    {
        // Vertical movement is dominant
        m_CurrentDirection = Direction::vertical;
        normalizedDirection.x = 0;
        normalizedDirection.y = glm::sign(normalizedDirection.y);
    }

}

void dae::GridMovementComponent::SnapPlayerToCell(const glm::vec2& currentPosition, glm::vec2 newPosition, Transform* pPlayerTransform)
{
    // Snap player's position with the gridlines
    if (m_CurrentDirection == Direction::horizontal && abs(m_TargetCell.dstRect.y - currentPosition.y) <= m_SnapRange)
    {
        newPosition.y = static_cast<float>(m_CurrentCell.dstRect.y);
        pPlayerTransform->SetPosition(newPosition);
    }
    else if (m_CurrentDirection == Direction::vertical && abs(m_TargetCell.dstRect.x - currentPosition.x) <= m_SnapRange)
    {
        newPosition.x = static_cast<float>(m_CurrentCell.dstRect.x);
        pPlayerTransform->SetPosition(newPosition);
    }
}



bool dae::GridMovementComponent::IsPlayerInGrid(const glm::vec2& newPosition)
{
    return (newPosition.x >= m_GridOffset.x && newPosition.x + m_CellSize.x <= m_GridOffset.x + m_pGrid->GetNrColumns() * m_CellSize.x &&
        newPosition.y >= m_GridOffset.y && newPosition.y + m_CellSize.y <= m_GridOffset.y + m_pGrid->GetNrRows() * m_CellSize.y);
}


void dae::GridMovementComponent::Render()
{
#ifdef _DEBUG
    SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();

    // current cell  
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green color
    SDL_RenderDrawRect(renderer, &m_CurrentCell.dstRect);

    // target cell
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // bleu color
    SDL_RenderDrawRect(renderer, &m_TargetCell.dstRect);

    // player
    //SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // purple color
    //SDL_Rect sprite{ static_cast<int>(GetOwner()->GetTransform()->GetWorldPosition().x), static_cast<int>(GetOwner()->GetTransform()->GetWorldPosition().y), 24, 24 }; // debug purpose
    //SDL_RenderDrawRect(renderer, &sprite);
#endif
}

void dae::GridMovementComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}

const float dae::GridMovementComponent::GetSpeed() const
{
    return m_Speed;
}
