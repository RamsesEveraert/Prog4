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

void dae::Player::InitPlayer(bool isPlayer1)
{
    AddRequiredComponents(isPlayer1);
}

void dae::Player::ResetPlayerStartPosition()
{
    auto startPosition{ m_pGrid->GetPlayerStartPoint() };
    GetOwner()->GetTransform()->SetPosition(startPosition);
}

void dae::Player::AddRequiredComponents(bool isPlayer1)
{
    GameObject* owner{ GetOwner() };
    std::cout << "Adding Required Components Player \n";

    glm::vec2 spriteOffsetP1 { 128, 16 };
    glm::vec2 spriteOffsetP2 { 75, 75 };

    std::string spritePathP1{ "General Sprites.png" };
    std::string spritePathP2{ "General_Sprites.png" };

    float spriteScale{ 1.5f };
    glm::vec2 spriteSize{ 16, 16 };

    if (isPlayer1)
    {
        owner->AddComponent<Sprite>(spritePathP1, SDL_Rect(static_cast<int>(spriteOffsetP1.x), static_cast<int>(spriteOffsetP1.y), static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)), spriteScale);
        std::cout << "Added Sprite comp Player \n";
    }
    else
    {
        owner->AddComponent<Sprite>(spritePathP2, SDL_Rect(static_cast<int>(spriteOffsetP2.x), static_cast<int>(spriteOffsetP2.y), static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)), spriteScale);
        std::cout << "Added Sprite comp Player \n";
    }
    

    isPlayer1 ? owner->GetTransform()->SetPosition(m_pGrid->GetPlayerStartPoint()) : owner->GetTransform()->SetPosition(m_pGrid->GetOponentStartPoint());
    
    glm::vec2 centerSprite{ GetOwner()->GetSpriteCenterPoint() };

    owner->AddComponent<BoxCollider>(centerSprite.x, centerSprite.y, spriteSize.x * spriteScale, spriteSize.y * spriteScale);
    std::cout << "Added box colldier Player \n";

    auto health = owner->AddComponent<Health>(); 
    health->Initialize();
    std::cout << "Added Health comp Player \n"; 

    owner->AddComponent<Score>(); 
    std::cout << "Added Score comp Player \n";
    
}
    


