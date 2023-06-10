#include "PookaNormalState.h"

#include "GameObject.h"
#include "SDL.h"

// singletons

#include "Timer.h"

//components

#include "Sprite.h"
#include "Transform.h"

// utilities


using namespace dae;

dae::PookaNormalState::PookaNormalState(GameObject* pPooka, GameObject* pPlayer, Grid* pGrid)
    : m_pPooka {pPooka}
    , m_pPlayer {pPlayer}
    , m_pGrid {pGrid}
    , m_GhostTime {6.f}
    , m_NormalTime{}
    , m_TransitionTime{}
    , m_HuntRange {30.f}
    , m_Speed {50.f}
    , m_PookaDirection{}
    , m_TargetCell {}
    , m_CurrentCell{}
{
}

void dae::PookaNormalState::OnEnter()
{
    SDL_Rect spriteSrc{0, 144, 16, 16};  // offset x, y , w, h
    m_pPooka->GetComponent<Sprite>()->SetSpriteSrc(spriteSrc);

    // reset time being in normal state
    m_NormalTime = 0.f;

    // give a random time to become a ghost
    float minTransitionTime{ 6.f };
    float maxTransitionTime{ 10.f };
    m_TransitionTime = static_cast<float>(rand()) / RAND_MAX * (maxTransitionTime - minTransitionTime) + minTransitionTime;

    // random start direction

    m_PookaDirection = GetRandomDirection();



}

void dae::PookaNormalState::OnEnd()
{
}

std::unique_ptr<PookaStateInterface> dae::PookaNormalState::Update()
{
    UpdateMovement();
    return std::unique_ptr<PookaNormalState>();
}

void dae::PookaNormalState::UpdateMovement()
{
    // get position of pooka and player
    glm::vec2 playerPosition{ m_pPlayer->GetTransform()->GetWorldPosition() };
    glm::vec2 pookaPosition{ m_pPooka->GetTransform()->GetWorldPosition() };

    glm::vec2 newPosition = pookaPosition + m_PookaDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed;

  /*  // check if pooka is in range of player , if so it hunts the player

    if (abs(playerPosition.x - pookaPosition.x) <= m_HuntRange && abs(playerPosition.x - pookaPosition.x) <= m_HuntRange)
    {
        // get the desired direction to the player
        glm::vec2 directionPooka{ glm::normalize(playerPosition - pookaPosition) };
    }
    else
    {
        // check if player can move to the next cell
       
    }


    // Get current Cell of Pooka
    const int currentCellIdx = m_pGrid->GetCellIdxFromPosition(pookaPosition);
    m_CurrentCell = m_pGrid->GetCells()[currentCellIdx];

    // Get first cell in direction of the player

    */

}

bool dae::PookaNormalState::CanMove(const glm::vec2& /*pookaPosition*/)
{
    // check if pooka can move

    if (m_TargetCell.IsDug) return true;

    //int distanceTargetCell{abs(m_TargetCell.dstRect.x)};

   // else if (!m_TargetCell.IsDug && abs(m_pPooka->GetComponent<>)) 

    return false;
}

glm::vec2 dae::PookaNormalState::GetRandomDirection() const
{
    // Random value between -1 and 1

    int randomX = (rand() % 3) - 1; 
    int randomY = (rand() % 3) - 1; 

    // one direction has to be 0

    if (randomX != 0 && randomY != 0)
    {
        randomX = (rand() % 2 == 0) ? 0 : randomX;
        randomY = (randomX == 0) ? ((rand() % 2 == 0) ? 1 : -1) : 0;
    }

    return glm::vec2(randomX, randomY);
}

