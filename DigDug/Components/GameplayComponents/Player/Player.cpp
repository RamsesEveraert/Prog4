#include "Player.h"

#include "GameObject.h"

//components
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Health.h"
#include "Score.h"
#include "SpriteAnimation.h"
#include "MovementComponent.h"
using namespace dae;

void dae::Player::InitPlayer()
{
    AddRequiredComponents();
    // todo add method to define sprite for player 1 , player 2 etc...
}

void dae::Player::AddRequiredComponents()
{
    /* requitred components

    - Sprite
    - sprite renderer
    - Health
    - Score
    - Animation
    - Movement Component

    */

    GameObject* owner{ GetOwner() };
    std::cout << "Adding Required Components Player \n";

    owner->AddComponent<Sprite>("General_Sprites.png", SDL_Rect(75, 58, 16, 16), 1.5f); 
    std::cout << "Added Sprite comp Player \n";

    owner->AddComponent<SpriteRenderer>();
    std::cout << "Added SpriteRenderer comp Player \n";
    
    owner->AddComponent<Health>(); 
    std::cout << "Added Health comp Player \n"; 

    owner->AddComponent<Score>(); 
    std::cout << "Added Score comp Player \n";
    
    //if (!owner->HasComponent<Animation>()) { owner->AddComponent<Animation>(); std::cout << "Added Animation comp Player \n"; }
   // if (!owner->HasComponent<MovementComponent>()) { owner->AddComponent<MovementComponent>(40.f); std::cout << "Added MoveComponent Player \n"; }
}
    


