#include "GridMovementComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Grid.h"
#include "Sprite.h"

#include "Timer.h"

#include "Renderer.h"

// debug purpose

#include <SDL.h>

using namespace dae;

Grid::Cell GridMovementComponent::m_CurrentCell{}; // had to be static because every direction button needs acces to the same variable
Grid::Cell GridMovementComponent::m_TargetCell{};
Grid::Cell GridMovementComponent::m_PreviousCell{};

dae::GridMovementComponent::GridMovementComponent(float speed, Grid* pGrid)
    : m_CurrentDirection{}
    , m_PreviousDirection {}
    , m_Speed{ speed }
    , m_pGrid{ pGrid }
    , m_PreviousCellIdx{}
    , m_SnapRange {12.f}
    , m_CellSize{ static_cast<glm::ivec2>(pGrid->GetCellSize()) }
    , m_GridOffset{ static_cast<glm::ivec2>(pGrid->GetGridPosition()) }
    , m_GridSize{ static_cast<glm::ivec2>(pGrid->GetGridSize()) }
    , m_Cells{ pGrid->GetCells() }
{
}


//************ TODO: only works for joystick not for dpad  *******************************//

//void dae::GridMovementComponent::Move(const glm::vec2& direction)
//{
//    // Get the current center position of the sprite
//    Transform* pPlayerTransform{ GetOwner()->GetTransform() };
//    const glm::vec2 currentPosition{ pPlayerTransform->GetWorldPosition() };
//
//    // get center position of player
//    const glm::vec2 spriteSize{ GetOwner()->GetComponent<Sprite>()->GetSize() };
//    const glm::vec2 playerCenter{ currentPosition.x + spriteSize.x / 2, currentPosition.y + spriteSize.y / 2 };
//
//    // Find the current tile
//    UpdateCurrenCell(playerCenter);
//
//    // Normalize direction
//    glm::vec2 normalizedDirection{ glm::normalize(direction) };
//
//    // Check the dominant movement
//    const float absX = std::abs(normalizedDirection.x);
//    const float absY = std::abs(normalizedDirection.y);
//
//    if (absX > absY)
//    {
//        // Horizontal movement is dominant
//        m_CurrentDirection = Direction::horizontal;
//        normalizedDirection.x = glm::sign(normalizedDirection.x);
//        normalizedDirection.y = 0;
//    }
//    else
//    {
//        // Vertical movement is dominant
//        m_CurrentDirection = Direction::vertical;
//        normalizedDirection.x = 0;
//        normalizedDirection.y = glm::sign(normalizedDirection.y);
//    }
//
//    // Calculate the new position of the sprite based on the given direction
//    glm::vec2 newPosition{ currentPosition + (normalizedDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed) };
//
//
//    // Check if the new position is within the bounds of the grid
//    if (newPosition.x >= m_GridOffset.x && newPosition.x + m_CellSize.x <= m_GridOffset.x + m_pGrid->GetNrColumns() * m_CellSize.x &&
//        newPosition.y >= m_GridOffset.y && newPosition.y + m_CellSize.y <= m_GridOffset.y + m_pGrid->GetNrRows() * m_CellSize.y)
//    {
//        // Find the next tile in direction of the movement
//        UpdateTargetCell(normalizedDirection);
//
//        // check if the player changes the direction
//        if (m_PreviousDirection != m_CurrentDirection)
//        {
//            // check if the player can change his direction + move : player has to be in bounds of the grid + withing snaprange of the center of the next cell
//            // player center has to be in snap range of targetcell center before it can snap and move
//
//            const glm::vec2 tileSize{ m_pGrid->GetCellSize() };
//            const glm::vec2 targetCellCenter{ m_TargetCell.dstRect.x + tileSize.x / 2, m_TargetCell.dstRect.y + tileSize.y / 2 };
//
//            // Calculate the offset from the target cell's center to the player's center
//            glm::vec2 offsetFromCenter = playerCenter - targetCellCenter;
//
//            if ((m_CurrentDirection == Direction::horizontal && std::abs(offsetFromCenter.x) <= m_SnapRange)
//                || (m_CurrentDirection == Direction::vertical && std::abs(offsetFromCenter.y) <= m_SnapRange))
//            {
//                // Snap player to target grid center
//                glm::vec2 snappedPosition = targetCellCenter - spriteSize * 0.5f;
//                pPlayerTransform->SetPosition(snappedPosition);
//                // Move player
//                const glm::vec2 newDirectionPosition = snappedPosition + (normalizedDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed);
//                pPlayerTransform->SetPosition(newDirectionPosition);
//            }
//            else
//            {
//                pPlayerTransform->SetPosition(newPosition);
//            }
//        }
//        else
//        {
//            pPlayerTransform->SetPosition(newPosition);
//        }
//    }
//    m_PreviousDirection = m_CurrentDirection;
//}


void dae::GridMovementComponent::Move(const glm::vec2& direction)
{
    // Get the current center position of the sprite
    Transform* pPlayerTransform{ GetOwner()->GetTransform() };
    const glm::vec2 currentPosition{ pPlayerTransform->GetWorldPosition() };
    const glm::vec2 spriteSize{ GetOwner()->GetComponent<Sprite>()->GetSize() };
    const glm::vec2 playerCenter{ currentPosition + spriteSize * 0.5f };

    // Find the current and target cells
    UpdateCurrenCell(playerCenter);
    UpdateTargetCell(direction);

    // Normalize direction
    glm::vec2 normalizedDirection{ glm::normalize(direction) };

    // Set the Direction axis
    SetDirectionAxis(normalizedDirection);

   // Calculate the new position of the sprite based on the given direction
    glm::vec2 newPosition{ currentPosition + (normalizedDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed) };


    // Check if the new position is within the bounds of the grid
    if (IsPlayerInGrid(newPosition))
    {
        // Find the next tile in direction of the movement
        UpdateTargetCell(normalizedDirection);
           
        // check if the player changes the direction
        if (m_PreviousDirection != m_CurrentDirection)
        {
            // check if the player can change his direction + move : player has to be in bounds of the grid + withing snaprange of the center of the next cell
            // player center has to be in snap range of targetcell center before it can snap and move

            const glm::vec2 tileSize{ m_pGrid->GetCellSize() };
            const glm::vec2 targetCellCenter{ m_TargetCell.dstRect.x + tileSize.x / 2, m_TargetCell.dstRect.y + tileSize.y / 2 };

            // Calculate the offset from the target cell's center to the player's center
            glm::vec2 offsetFromCenter = playerCenter - targetCellCenter;

            if ((m_CurrentDirection == Direction::horizontal && std::abs(offsetFromCenter.x) <= m_SnapRange)
                || (m_CurrentDirection == Direction::vertical && std::abs(offsetFromCenter.y) <= m_SnapRange))
            {
                // Snap player to target grid center
                glm::vec2 snappedPosition{ glm::vec2(m_TargetCell.dstRect.x + m_TargetCell.dstRect.w * 0.5f,
                                         m_TargetCell.dstRect.y + m_TargetCell.dstRect.h * 0.5f) - spriteSize * 0.5f };
                pPlayerTransform->SetPosition(snappedPosition);
            }
            else
            {
                pPlayerTransform->SetPosition(newPosition);
            }
        }
        else
        {
            pPlayerTransform->SetPosition(newPosition);
        }
    }
    m_PreviousDirection = m_CurrentDirection;
}

//void dae::GridMovementComponent::Move(const glm::vec2& direction)
//{
//    // Get the current center position of the sprite
//    Transform* pPlayerTransform = GetOwner()->GetTransform();
//    const glm::vec2 currentPosition = pPlayerTransform->GetWorldPosition();
//    const glm::vec2 spriteSize = GetOwner()->GetComponent<Sprite>()->GetSize();
//    const glm::vec2 playerCenter = currentPosition + spriteSize * 0.5f;
//
//    // Find the current and target cells
//    UpdateCurrenCell(playerCenter);
//    UpdateTargetCell(direction);
//
//    // Normalize direction
//    glm::vec2 normalizedDirection = glm::normalize(direction);
//
//    // Set the Direction axis
//    SetDirectionAxis(normalizedDirection);
//
//    // Calculate the new position of the sprite based on the given direction
//    glm::vec2 newPosition = currentPosition + (normalizedDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed);
//
//    // Check if the new position is within the bounds of the grid
//    if (IsPlayerInGrid(newPosition))
//    {
//        // Check if the player changes direction
//
//        if (m_PreviousDirection != m_CurrentDirection)
//        {
//            // check if the player can change his direction + move : player has to be in bounds of the grid + withing snaprange of the center of the next cell
//            // player center has to be in snap range of targetcell center before it can snap and move
//
//            const glm::vec2 tileSize{ m_pGrid->GetCellSize() };
//            const glm::vec2 targetCellCenter{ m_TargetCell.dstRect.x + tileSize.x / 2, m_TargetCell.dstRect.y + tileSize.y / 2 };
//
//            // Calculate the offset from the target cell's center to the player's center
//            glm::vec2 offsetFromCenter = playerCenter - targetCellCenter;
//
//            if ((m_CurrentDirection == Direction::horizontal && std::abs(offsetFromCenter.x) <= m_SnapRange)
//                || (m_CurrentDirection == Direction::vertical && std::abs(offsetFromCenter.y) <= m_SnapRange))
//            {
//
//                // Snap player to target grid center
//                glm::vec2 snappedPosition{ glm::vec2(m_TargetCell.dstRect.x + m_TargetCell.dstRect.w * 0.5f,
//                                         m_TargetCell.dstRect.y + m_TargetCell.dstRect.h * 0.5f) - spriteSize * 0.5f };
//
//                pPlayerTransform->SetPosition(snappedPosition);
//            }
//            else
//            {
//                // Move player
//                pPlayerTransform->SetPosition(newPosition);
//            }
//
//
//        }
//        pPlayerTransform->SetPosition(newPosition);
//    }
//
//    m_PreviousDirection = m_CurrentDirection;
//}




void dae::GridMovementComponent::UpdateCurrenCell(const glm::vec2& currentPosition)
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
bool dae::GridMovementComponent::IsPlayerInGrid(const glm::vec2& newPosition)
{
    return (newPosition.x >= m_GridOffset.x && newPosition.x + m_CellSize.x <= m_GridOffset.x + m_pGrid->GetNrColumns() * m_CellSize.x &&
        newPosition.y >= m_GridOffset.y && newPosition.y + m_CellSize.y <= m_GridOffset.y + m_pGrid->GetNrRows() * m_CellSize.y);
}



void dae::GridMovementComponent::Render()
{
    SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();

    // current cell  
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green color
    SDL_RenderDrawRect(renderer, &m_CurrentCell.dstRect);

    // Next cell
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // bleu color
    SDL_RenderDrawRect(renderer, &m_TargetCell.dstRect);

}

void dae::GridMovementComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}

const float dae::GridMovementComponent::GetSpeed() const
{
    return m_Speed;
}
