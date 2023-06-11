#include "Pooka.h"

#include "GameObject.h"

//components
#include "Transform.h"
#include "Sprite.h"
#include "BoxCollider.h"
#include "Health.h"
#include "GridMovementComponent.h"


// states
#include "PookaNormalState.h"

dae::Pooka::Pooka(GameObject* pPlayer, Grid* pGrid, int indexEnemy)
	: m_pState {nullptr}
	, m_pPlayer{pPlayer}
	, m_pGrid {pGrid}
	, m_IndexEnemy{indexEnemy}
{
	
}

void dae::Pooka::Initialize()
{
	GameObject* owner{ GetOwner() };

	glm::vec2 spriteSize{ 16, 16 };
	glm::vec2 spriteOffset{ 0, 160 };
	float spriteScale{ 1.5f };

	owner->AddComponent<Sprite>("General Sprites.png", SDL_Rect(static_cast<int>(spriteOffset.x), static_cast<int>(spriteOffset.y), static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)), spriteScale);
	std::cout << "Added Sprite comp Enemy \n";

	owner->GetTransform()->SetPosition(m_pGrid->GetPookaStartPoints()[m_IndexEnemy]);

	glm::vec2 centerSprite{ GetOwner()->GetSpriteCenterPoint() };

	owner->AddComponent<BoxCollider>(centerSprite.x, centerSprite.y, spriteSize.x * spriteScale, spriteSize.y * spriteScale);
	std::cout << "Added Box collider Enemy \n";

	owner->AddComponent<Health>();
	std::cout << "Added Health comp Enemy \n";

	float speed{ 50.f };
	owner->AddComponent<GridMovementComponent>(speed, m_pGrid);


	ChangeState(std::make_unique<PookaNormalState>(GetOwner(), m_pPlayer, m_pGrid));
}

void dae::Pooka::Update()
{
	std::unique_ptr<PookaStateInterface> pNewState{ m_pState->Update() };
	if (pNewState) ChangeState(std::move(pNewState));
}

void dae::Pooka::ChangeState(std::unique_ptr<PookaStateInterface> pState)
{
	if (m_pState) m_pState->OnEnd();

	m_pState = std::move(pState);
	m_pState->OnEnter();
}
