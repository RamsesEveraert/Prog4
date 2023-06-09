#include "Player.h"

#include "GameObject.h"

//components
#include "Sprite.h"
#include "Health.h"
#include "Score.h"
#include "SpriteAnimation.h"
#include "MovementComponent.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Grid.h"

using namespace dae;

dae::Player::Player(Grid* pGrid)
    : m_pGrid{pGrid}
{
}

void dae::Player::InitPlayer()
{
    AddRequiredComponents();
    // todo add method to define sprite for player 1 , player 2 etc...
}

void dae::Player::ResetPlayerStartPosition()
{
    auto startPosition{ m_pGrid->GetPlayerStartPoint() };
    GetOwner()->GetTransform()->SetPosition(startPosition);
}

void dae::Player::AddRequiredComponents()
{
    GameObject* owner{ GetOwner() };
    std::cout << "Adding Required Components Player \n";

    glm::vec2 spriteOffset{ 128, 16 };
    float spriteScale{ 1.5f };
    glm::vec2 spriteSize{ 16, 16 };

    owner->AddComponent<Sprite>("General Sprites.png", SDL_Rect(static_cast<int>(spriteOffset.x), static_cast<int>(spriteOffset.y), static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)), spriteScale);
    std::cout << "Added Sprite comp Player \n";

    owner->GetTransform()->SetPosition(m_pGrid->GetPlayerStartPoint());
    
    glm::vec2 centerSprite{ GetOwner()->GetSpriteCenterPoint() };

    owner->AddComponent<BoxCollider>(centerSprite.x, centerSprite.y, spriteSize.x * spriteScale, spriteSize.y * spriteScale);
    std::cout << "Added box colldier Player \n";

    auto health = owner->AddComponent<Health>(); 
    health->Initialize();
    std::cout << "Added Health comp Player \n"; 

    owner->AddComponent<Score>(); 
    std::cout << "Added Score comp Player \n";
    
}
    


