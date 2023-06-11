#include "PookaGhostState.h"

//components:
#include "GameObject.h"
#include "Grid.h"
#include "Transform.h"
#include "Sprite.h"
#include "GridMovementComponent.h"

// states
#include "PookaNormalState.h"

//singletons
#include "Timer.h"

using namespace dae;

dae::PookaGhostState::PookaGhostState(GameObject* pPooka, GameObject* pPlayer, Grid* pGrid)
    : m_pPooka{ pPooka }
    , m_pPlayer{ pPlayer }
    , m_pGrid {pGrid}
    , m_pPookaTransform{}
    , m_GhostFormTime{}
    , m_TransitionTime{1.5f}
    ,m_Speed {50.f}
{
}

void dae::PookaGhostState::OnEnter()
{
    m_pPookaTransform = m_pPooka->GetTransform();
    SDL_Rect spriteSrc{ 48, 144, 16, 16 };  // offset x, y , w, h
    m_pPooka->GetComponent<Sprite>()->SetSpriteSrc(spriteSrc);
    std::cout << "entered GhostState \n";
}

void dae::PookaGhostState::OnEnd()
{

}

std::unique_ptr<PookaStateInterface> dae::PookaGhostState::Update()
{
    m_pPookaTransform = m_pPooka->GetTransform();

    const glm::vec2 posPooka{ m_pPookaTransform->GetWorldPosition() };
    const glm::vec2 posPlayer{ m_pPlayer->GetTransform()->GetWorldPosition() };
    const glm::vec2 chaseDirection{ posPlayer - posPooka };

    glm::vec2 newPosition = posPooka + glm::normalize(chaseDirection) * TimeManager::GetInstance().GetDeltaTimeSec() * m_Speed;
    m_pPookaTransform->SetPosition(newPosition);

    if (m_GhostFormTime < m_TransitionTime) m_GhostFormTime += TimeManager::GetInstance().GetDeltaTimeSec();
    else
    {
        std::cout << "transition is over \n ";
        if (m_pPooka->GetComponent<GridMovementComponent>()->GetCurrentCell().IsDug)
        {
            std::cout << "current cell is dug \n";
            return std::make_unique<PookaNormalState>(m_pPooka, m_pPlayer, m_pGrid);
        }
    }

    return nullptr;
}
