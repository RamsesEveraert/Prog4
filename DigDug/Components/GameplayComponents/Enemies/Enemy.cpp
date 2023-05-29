#include "Enemy.h"

#include "GameObject.h"

//components
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Health.h"
#include "Score.h"
#include "SpriteAnimation.h"
#include "MovementComponent.h"
#include "BoxCollider.h"
#include "Grid.h"
#include "Transform.h"

using namespace dae;

dae::Enemy::Enemy(Grid* pGrid, int indexEnemy)
    : m_pGrid{pGrid}
    , m_IndexEnemy{indexEnemy}
{
}

void dae::Enemy::InitEnemy()
{
    AddRequiredComponents();
}

void dae::Enemy::AddRequiredComponents()
{
    /* requitred components

    - Sprite
    - sprite renderer
    - Health
    - Animation
    - Movement Component
    - collisionbox

    */

    GameObject* owner{ GetOwner() };
    std::cout << "Adding Required Components Enemy \n";

    glm::vec2 spriteSize{ 16, 16 };
    glm::vec2 spriteOffset{ 0, 160 };
    float spriteScale{ 1.5f };

    owner->AddComponent<Sprite>("General Sprites.png", SDL_Rect(static_cast<int>(spriteOffset.x), static_cast<int>(spriteOffset.y), static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)), spriteScale);
    std::cout << "Added Sprite comp Enemy \n";

    owner->AddComponent<SpriteRenderer>();
    std::cout << "Added SpriteRenderer comp Enemy \n";

    owner->GetTransform()->SetPosition(m_pGrid->GetPookaStartPoints()[m_IndexEnemy]);

    glm::vec2 centerSprite{ GetOwner()->GetSpriteCenterPoint() };

    owner->AddComponent<BoxCollider>(centerSprite.x, centerSprite.y, spriteSize.x * spriteScale, spriteSize.y * spriteScale);
    std::cout << "Added Box collider Enemy \n";

    owner->AddComponent<Health>();
    std::cout << "Added Health comp Enemy \n";


    //if (!owner->HasComponent<Animation>()) { owner->AddComponent<Animation>(); std::cout << "Added Animation comp Player \n"; }
   // if (!owner->HasComponent<MovementComponent>()) { owner->AddComponent<MovementComponent>(40.f); std::cout << "Added MoveComponent Player \n"; }
}



