#include "Player.h"

#include "GameObject.h"

//components

#include "Health.h"
#include "Score.h"
//#include "Sprite.h"
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
    /* Check if components already exist if not : add them

    - Health
    - Score
    - Sprite
    - Animation
    - Movement Component

    */


    GameObject* owner{ GetOwner() };
    std::cout << "Adding Required Components Player \n";

    if (!owner->HasComponent<Health>()) { owner->AddComponent<Health>(); std::cout << "Added Health comp Player \n"; }
    if (!owner->HasComponent<Score>()) {  owner->AddComponent<Score>(); std::cout << "Added Score comp Player \n";}
    //if (!owner->HasComponent<Sprite>()) { owner->AddComponent<Sprite>(); std::cout << "Added Sprite comp Player \n"; }
    //if (!owner->HasComponent<Animation>()) { owner->AddComponent<Animation>(); std::cout << "Added Animation comp Player \n"; }
   // if (!owner->HasComponent<MovementComponent>()) { owner->AddComponent<MovementComponent>(40.f); std::cout << "Added MoveComponent Player \n"; }
}
    


