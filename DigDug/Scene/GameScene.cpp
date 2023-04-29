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
#include "Grid.h"
#include "GridMovementComponent.h"


// commands
#include "MoveStickCommand.h"
#include "MoveCommand.h"
#include "GridMoveCommand.h"






void dae::GameScene::LoadScene()
{
	// Create scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background

	CreateBackground(scene);

	// Create Grid
	CreateGrid(scene);

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
	pPlayer->GetTransform()->SetWorldPosition(250.f, 150.f);

	scene.Add(pPlayer);
}

void dae::GameScene::CreateGrid(Scene& scene)
{
	const glm::vec2 positionGrid{ 0.f,100.f };
	const float gameScale{ 1.5f };
	const glm::vec2 sizeGrid{ 240.f * gameScale, 256.f * gameScale };
	const float sizeTiles{ gameScale * 16.f };

	auto grid = std::make_shared<GameObject>("grid");
	grid->AddComponent<Grid>(sizeGrid.x, sizeGrid.y, sizeTiles, positionGrid);

	scene.Add(grid);
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
	auto GridObj = scene.FindObject("grid");
	auto grid = GridObj->GetComponent<Grid>();

	auto spriteObj{ std::make_shared<GameObject>("SpriteTest") };
	spriteObj->GetTransform()->SetPosition(grid->GetGridPosition());
	spriteObj->AddComponent<Sprite>("General_Sprites.png", SDL_Rect(75, 58, 16, 16), 1.5f);
	spriteObj->AddComponent<SpriteRenderer>();	

	scene.Add(spriteObj);

	// controller

	auto controller = dae::InputManager::GetInstance().AddController();
	auto player = spriteObj.get();

	//	dpad controls

	std::vector<std::pair<dae::ControllerInput::ControllerButtons, glm::vec2>> buttonDirections = {
		{ dae::ControllerInput::ControllerButtons::DPadUp, {0.f, -1.f} },
		{ dae::ControllerInput::ControllerButtons::DPadDown, {0.f, 1.f} },
		{ dae::ControllerInput::ControllerButtons::DPadRight, {1.f, 0.f} },
		{ dae::ControllerInput::ControllerButtons::DPadLeft, {-1.f, 0.f} }
	};

	for (auto& buttonDirection : buttonDirections)
	{
		auto button = std::make_pair(buttonDirection.first, dae::ControllerInput::ButtonState::Pressed);
		auto direction = buttonDirection.second;
		float speed{ 40.f };

		auto pGridMoveCommand = std::make_shared<GridMoveCommand>(player, speed, direction, grid);
		controller->AttachCommandToButton(pGridMoveCommand, button);
	}	

	
}
