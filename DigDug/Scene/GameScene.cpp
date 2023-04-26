#include "GameScene.h"

#include <SDL.h>

#include "GameObject.h"
#include "Scene.h"

// managers
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

// components
#include "Player.h"
#include "Text.h"
#include "Texture.h"
#include "TextureRenderer.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "FPSComponent.h"

// commands
#include "MoveStickCommand.h"
#include "MoveCommand.h"






void dae::GameScene::LoadScene()
{
	// Create scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background

	CreateBackground(scene);

	// player
	CreatePlayer(scene);
	std::cout << "Player created! \n";

	// sprite test
	SpriteTest(scene);

	// fps test

	CreateFPSObject(scene);
	


}

void dae::GameScene::CreatePlayer(Scene& scene)
{
	auto pPlayer{ std::make_shared<GameObject>("player") };
	pPlayer->AddComponent<Player>()->InitPlayer();

	scene.Add(pPlayer);
}

// temporary

void dae::GameScene::CreateFPSObject(Scene& scene)
{
	auto fpsCounter = std::make_shared<dae::GameObject>("fpsCounter");
	fpsCounter->GetTransform()->SetPosition(glm::vec2{ 20,20 });
	fpsCounter -> AddComponent<Texture>(""); // empty texture
	auto fpsComponent = fpsCounter->AddComponent<dae::FPSComponent>();
	fpsComponent->SetColor(SDL_Color{255,0,0});
	scene.Add(fpsCounter);
}


void dae::GameScene::CreateBackground(Scene& scene)
{
	auto background = std::make_shared<dae::GameObject>("background");
	background->AddComponent<Texture>("background.tga");
	background->AddComponent<TextureRenderer>();

	scene.Add(background);
}

void dae::GameScene::SpriteTest(Scene& scene)
{
	auto spriteObj{ std::make_shared<GameObject>("SpriteTest") };
	spriteObj->AddComponent<Sprite>("General_Sprites.png", SDL_Rect(75, 58, 16, 16), 2.f);
	spriteObj->AddComponent<SpriteRenderer>();

	scene.Add(spriteObj);

	auto controller = dae::InputManager::GetInstance().AddController();
	auto player = spriteObj.get();

	// thumbsticks controls
	auto button = ControllerInput::ControllerButtons::LeftThumbstick;
	float stickSpeed{ 40.f };
	auto pMoveCommandStick = std::make_shared<dae::MoveStickCommand>(player, stickSpeed, controller->GetDirectionLeftThumbStick());
	controller->AttachCommandToThumbStick(pMoveCommandStick, button);

	
}
