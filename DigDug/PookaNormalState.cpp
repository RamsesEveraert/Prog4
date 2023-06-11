#include "PookaNormalState.h"

#include "GameObject.h"
#include "SDL.h"
#include "glm/glm.hpp"

// singletons

#include "Timer.h"
#include "EventHandler.h"

//components

#include "Sprite.h"
#include "Transform.h"
#include "GridMovementComponent.h"

// utilities
#include "Event.h"


using namespace dae;

dae::PookaNormalState::PookaNormalState(GameObject* pPooka, GameObject* pPlayer, Grid* pGrid)
    : m_pPooka {pPooka}
    , m_pPlayer {pPlayer}
    , m_pPookaTransform{}
    , m_pGrid {pGrid}
    , m_GhostTime {6.f}
    , m_NormalTime{}
    , m_TransitionTime{}
    , m_HuntRange {30.f}
    , m_Speed {50.f}
    , m_PookaDirection{}
    , m_TargetCell {}
    , m_CurrentCell{}
    , m_Cells{ pGrid->GetCells()}
{
    EventHandler::GetInstance().AddListener("PookaCantMove", [this](const dae::Event& event) { onCantMove(event); });
}

void dae::PookaNormalState::OnEnter()
{
    std::cout << "entered normal state \n";

    m_pPookaTransform = m_pPooka->GetTransform();
    SDL_Rect spriteSrc{0, 144, 16, 16};  // offset x, y , w, h
    m_pPooka->GetComponent<Sprite>()->SetSpriteSrc(spriteSrc);

    // reset time being in normal state
    m_NormalTime = 0.f;

    // give a random time to become a ghost
    float minTransitionTime{ 4.f };
    float maxTransitionTime{ 7.f };
    m_TransitionTime = static_cast<float>(rand()) / RAND_MAX * (maxTransitionTime - minTransitionTime) + minTransitionTime;

    // random start direction

    m_PookaDirection = GetRandomDirection();



}

void dae::PookaNormalState::OnEnd()
{
}

std::unique_ptr<PookaStateInterface> dae::PookaNormalState::Update()
{
    /*UpdateMovement();*/
    m_NormalTime += TimeManager::GetInstance().GetDeltaTimeSec();
    if (m_NormalTime > m_TransitionTime) return std::make_unique<PookaGhostState>(m_pPooka, m_pPlayer, m_pGrid);
    return nullptr;
}

void dae::PookaNormalState::UpdateMovement()
{
    m_pPooka->GetComponent<GridMovementComponent>()->Move(m_PookaDirection);
    //// get position of pooka and player
    //glm::vec2 playerPosition{ m_pPlayer->GetTransform()->GetWorldPosition() };
    //glm::vec2 pookaPosition{ m_pPooka->GetTransform()->GetWorldPosition() };


    //glm::vec2 newPosition = pookaPosition + m_PookaDirection * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed;

    //if (CanMove(newPosition))
    //{
    //    m_pPookaTransform->SetPosition(newPosition);
    //    return;
    //}

    //std::cout << "player can't move anymore \n";

}


void dae::PookaNormalState::onCantMove(const Event& event)
{
    GameObject* stuckPooka{};
    for (const auto& data : event.data)
    {
        if (data.type() == typeid(GridMovementComponent*))
        {
            stuckPooka = std::any_cast<GridMovementComponent*>(data)->GetOwner();
        }
    }

    if (m_pPooka != stuckPooka) return; // not this pooka

    m_PookaDirection = GetRandomDirection();
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

