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
#include "Health.h"
#include "Tile.h"

//HUD
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"


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

	//Create WorldTiles
	CreateWorldTiles(scene);

	// players
	CreatePlayers(scene);
	std::cout << "Player created! \n";

	// HUD
	SetupHUD(scene);
	std::cout << "HUD Created \n";

	// fps test
	CreateFPSObject(scene);
	


}

void dae::GameScene::CreatePlayers(Scene& scene)
{
	auto gridObj{ scene.FindObject("grid") };
	auto grid{ gridObj->GetComponent<Grid>() };

	auto player1{ std::make_shared<GameObject>("player1") };
	player1->AddComponent<Player>()->InitPlayer();
	player1->GetTransform()->SetPosition(grid->GetPlayerStartPoint());
	scene.Add(player1);

	auto controller{ InputManager::GetInstance().AddController() };

	// Create a map of buttons and their corresponding directions
	std::map<ControllerInput::ControllerButtons, glm::vec2> buttonDirections = {
		{ ControllerInput::ControllerButtons::DPadUp, { 0.f, -1.f } },
		{ ControllerInput::ControllerButtons::DPadDown, { 0.f, 1.f } },
		{ ControllerInput::ControllerButtons::DPadRight, { 1.f, 0.f } },
		{ ControllerInput::ControllerButtons::DPadLeft, { -1.f, 0.f } }
	};

	// Create a move command for each button/direction pair and attach it to the controller
	const float speed{ 40.f };
	for (const auto& [button, direction] : buttonDirections)
	{
		auto moveCommand{ std::make_shared<GridMoveCommand>(player1.get(), speed, direction, grid) };
		controller->AttachCommandToButton(moveCommand, { button, ControllerInput::ButtonState::Pressed });
	}

		// thumbsticks controls
	auto button = ControllerInput::ControllerButtons::LeftThumbstick;
	auto pMoveCommandStick{ std::make_shared<GridMoveCommand>(player1.get(), speed, controller->GetDirectionLeftThumbStick(), grid) };

	controller->AttachCommandToThumbStick(pMoveCommandStick, button);

	// keyboard controls

	auto keyboard = dae::InputManager::GetInstance().AddKeyboard();

	std::vector<std::pair<SDL_Scancode, glm::vec2>> keyDirections = {
	{ SDL_SCANCODE_W, {0.f, -1.f} },
	{ SDL_SCANCODE_S, {0.f, 1.f} },
	{ SDL_SCANCODE_D, {1.f, 0.f} },
	{ SDL_SCANCODE_A, {-1.f, 0.f} }
	};

	for (auto& keyDirection : keyDirections)
	{
		auto keyPressed = std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Pressed);
		auto keyDown = std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Down);
		auto direction = keyDirection.second;
		auto pMoveCommand = std::make_shared<dae::GridMoveCommand>(player1.get(), speed, direction, grid);
		keyboard->AttachCommandToButton(pMoveCommand, keyPressed);
	}
}


void dae::GameScene::CreateGrid(Scene& scene)
{	
	const float gameScale{ 1.5f };
	const float sizeTiles{ gameScale * 16.f };
	const float rowTiles{ 14 };
	const float columnTiles{ 14 };
	const glm::vec2 positionGrid{ 0.f, 3 * sizeTiles };
	const glm::vec2 sizeGrid{ columnTiles * sizeTiles, rowTiles * sizeTiles };
	std::vector<std::string> levelLayout{};

	auto grid = std::make_shared<GameObject>("grid");
	/*auto gridComponent = */grid->AddComponent<Grid>(sizeGrid.x, sizeGrid.y, sizeTiles, positionGrid, levelLayout);

	// player start pos
	//gridComponent->SetPlayerStartPoint(4, 6);
	


	scene.Add(grid);
}

void dae::GameScene::CreateWorldTiles(Scene& scene)
{
	const auto gridObj{ scene.FindObject("grid") };
	auto grid{ gridObj->GetComponent<Grid>() };
	const auto gridCells{ gridObj->GetComponent<Grid>()->GetCells() };
	const float gameScale{ 1.5f };
	

	int tileNr{ 1 };

	for (const auto& cell : gridCells)
	{
		auto worldTile = std::make_shared<GameObject>("WorldTile" + std::to_string(tileNr++));
		worldTile->GetTransform()->SetPosition(static_cast<float>(cell.dstRect.x), static_cast<float>(cell.dstRect.y));
		worldTile->AddComponent<Tile>(cell.dstRect, grid, gameScale);



		if (cell.IsPlayerStartPoint)
		{
			SDL_Rect tunnel{ 128, 0, 16,16 };
			worldTile->AddComponent<Sprite>("General Sprites.png", tunnel, gameScale);
			worldTile->AddComponent<SpriteRenderer>();
		}
		scene.Add(worldTile);
	}

}

void dae::GameScene::SetupHUD(Scene& scene)
{
	// Get player 1 object
	auto player1Object = scene.FindObject("player1");

	// Add lives display for player 1
	glm::vec2 posLives{ 0.f, 408.f };

	auto livesPlayer1 = std::make_shared<dae::GameObject>("livesPlayer1");
	livesPlayer1->GetTransform()->SetPosition(posLives);
	auto display = livesPlayer1->AddComponent<LivesDisplayComponent>();
	display->SetOwnerLives(player1Object.get());
	scene.Add(livesPlayer1);

	// Add score display for player 1
	glm::vec2 posScore{ 110.f, 24.f};

	auto scorePlayer1 = std::make_shared<dae::GameObject>("ScorePlayer1");
	scorePlayer1->GetTransform()->SetPosition(posScore);
	scorePlayer1->AddComponent<ScoreDisplayComponent>()->SetOwnerScore(player1Object.get());
	scene.Add(scorePlayer1);
}

// temporary

void dae::GameScene::CreateFPSObject(Scene& scene)
{
	glm::vec2 posFPS{ 20,20 };
	SDL_Color color{ 255,0,0 };

	auto fpsCounter = std::make_shared<dae::GameObject>("fpsCounter");
	fpsCounter->GetTransform()->SetPosition(posFPS);
	fpsCounter -> AddComponent<Texture>(""); // empty texture
	auto fpsComponent = fpsCounter->AddComponent<dae::FPSComponent>();
	fpsComponent->SetColor(color);
	scene.Add(fpsCounter);
}


void dae::GameScene::CreateBackground(Scene& scene)
{
	const float gameScale{ 1.5f };
	auto background = std::make_shared<dae::GameObject>("background");
	/*background->AddComponent<Texture>("background.tga");
	background->AddComponent<TextureRenderer>();*/
	const SDL_Rect LvlOneBg{ 5,852,224,272 };
	background->AddComponent<Sprite>("Level_Backgrounds.png", LvlOneBg, gameScale);
	background->AddComponent<SpriteRenderer>();

	scene.Add(background);
}

void dae::GameScene::SpriteTest(Scene& scene)
{
	auto GridObj = scene.FindObject("grid");
	auto grid = GridObj->GetComponent<Grid>();

	const SDL_Rect& spriteSrc{ 75, 58, 16, 16 };
	const float gameScale{ 1.5f };

	auto spriteObj{ std::make_shared<GameObject>("SpriteTest") };
	spriteObj->GetTransform()->SetPosition(grid->GetGridPosition());
	spriteObj->AddComponent<Sprite>("General_Sprites.png", spriteSrc, gameScale);
	spriteObj->AddComponent<SpriteRenderer>();	

	scene.Add(spriteObj);

	// controller

	auto controller = dae::InputManager::GetInstance().AddController();
	auto player = spriteObj.get();

	//	dpad controls test

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

		// thumbsticks controls 
	auto button = ControllerInput::ControllerButtons::LeftThumbstick;
	float stickSpeed{ 40.f };
	auto pGridMoveCommand = std::make_shared<GridMoveCommand>(player, stickSpeed, controller->GetDirectionLeftThumbStick(), grid);

	controller->AttachCommandToThumbStick(pGridMoveCommand, button);
	
}
