#include "LevelManager.h"

// Singletons
#include "SceneManager.h"
#include "SpriteRenderer.h"
#include "TextureRenderer.h"
#include "EventQueue.h"
#include "InputManager.h"

// GameAssets
#include "GameObject.h"
#include "Event.h"
#include "Texture2D.h"

// Components
#include "Sprite.h"
#include "Texture.h"
#include "Grid.h"
#include "Tile.h"
#include "Transform.h"
#include "Player.h"
#include "Enemies/Enemy.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "FPSComponent.h"
#include "Button.h"
#include "BoxCollider.h"

// Commands
#include "GridMoveCommand.h"

// Other includes
#include <fstream>
#include <sstream>
#include <SDL.h>

void dae::LevelManager::LoadStartScreen()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartOptions");

	//********** Game Window *************//

	// Background
	auto background = std::make_shared<dae::GameObject>("background");
	background->AddComponent<Texture>("background.tga");
	background->AddComponent<TextureRenderer>();
	scene.Add(background);

	// School Logo
	auto logo = std::make_shared<dae::GameObject>("logo");
	logo->GetTransform()->SetPosition(glm::vec2{ 65.f,40.f });
	logo->AddComponent<Texture>("logo.tga");
	logo->AddComponent<TextureRenderer>();
	scene.Add(logo);

	// Game Logo
	auto gameLogo = std::make_shared<dae::GameObject>("gameLogo");
	gameLogo->GetTransform()->SetPosition(glm::vec2{ 65.f,135.f });
	gameLogo->AddComponent<Texture>("GameLogo.png");
	gameLogo->AddComponent<TextureRenderer>();
	scene.Add(gameLogo);

	//********** Game Modes  *************//

	// Single Player
	auto singlePlayer = std::make_shared<dae::GameObject>("SinglePlayer");
	glm::vec2 buttonPosition{ 95.f,285.f };
	singlePlayer->GetTransform()->SetPosition(buttonPosition);
	singlePlayer->AddComponent<Texture>("SinglePlayer.png");
	singlePlayer->AddComponent<TextureRenderer>();

	auto onClickSinglePlayer = [&]() { std::cout << "singleplayer button clicked \n"; LevelManager::GetInstance().LoadLevel(scene, GameMode::SINGLEPLAYER, 1); };
	const glm::vec2 sizeButton{ 150.f, 23.f };
	singlePlayer->AddComponent<Button>(buttonPosition, sizeButton, onClickSinglePlayer);

	scene.Add(singlePlayer);

	// Co_Op
	auto co_op = std::make_shared<dae::GameObject>("co_op");
	co_op->GetTransform()->SetPosition(glm::vec2{ 95.f, 315.f });
	co_op->AddComponent<Texture>("co_op.png");
	co_op->AddComponent<TextureRenderer>();
	scene.Add(co_op);

	// Versus
	auto versus = std::make_shared<dae::GameObject>("versus");
	versus->GetTransform()->SetPosition(glm::vec2{ 95.f, 345.f });
	versus->AddComponent<Texture>("Versus.png");
	versus->AddComponent<TextureRenderer>();
	scene.Add(versus);
}

void dae::LevelManager::LoadLevel(Scene& scene, GameMode mode, int nrLevel)
{
	// Reset Level
	m_GameMode = mode;
	m_NrLevel = nrLevel;

	ResetLevel(scene);

	// start new LevelScene
	auto& level = dae::SceneManager::GetInstance().CreateScene("Level");
	m_CurrentScene = &level;

	// parse data from file
	std::stringstream levelPath;
	levelPath << "../Data/level" << nrLevel << ".txt";

	std::ifstream levelFile{ levelPath.str() };

	if (!levelFile.is_open()) std::cout << "levelLayout can't be found \n";

	std::vector<std::string> levelLayout{}; // stores a row in ea index
	std::string line;

	while (std::getline(levelFile, line)) 
	{
		
		levelLayout.push_back(line); // pushback: copy needed
 	}

	levelFile.close();

	// Create Background
	CreateBackground(level, nrLevel);

	// Create Grid
	CreateGrid(level, levelLayout);

	// Create world tiles
	CreateWorldTiles(level);

	// Create Players
	CreatePlayer(level, mode);

	// Create Enemies
	CreateEnemies(level, mode);

	// Setup HUD
	SetupHUD(level);

	// Add (temporary) fps counter
	CreateFPSObject(level);

}

void dae::LevelManager::StartNextLevel(const Event& /*event*/)
{
}

void dae::LevelManager::ResetLevel(Scene& scene)
{
	if (!m_IsAddedAsListener)
	{
		EventQueue::GetInstance().AddListener("NextLevel", [this](const dae::Event& event) { StartNextLevel(event); });
		m_IsAddedAsListener = true;
	}

	dae::SceneManager::GetInstance().RemoveScene(&scene);
}

void dae::LevelManager::CreateBackground(Scene& scene, int nrLevel)
{
	const float gameScale{ 1.5f };
	auto background = std::make_shared<dae::GameObject>("background");
	int spriteGap = 10;
	glm::ivec2 offset = { 5, 852 };
	glm::ivec2 spriteSize = { 224, 272 };

	const SDL_Rect levelBackground{ offset.x + (nrLevel - 1) * (spriteSize.x + spriteGap) 
									,offset.y
									,spriteSize.x
									,spriteSize.y }; 

	background->AddComponent<Sprite>("Level_Backgrounds.png", levelBackground, gameScale);
	background->AddComponent<SpriteRenderer>();

	scene.Add(background);
}

void dae::LevelManager::CreateGrid(Scene& scene, const std::vector<std::string>& levelLayout)
{
	if (levelLayout.empty())
	{
		std::cout << "there is no level layout parsed \n";
		return;
	}

	const float sizeTiles{ m_GameScale * 16.f };
	const float rowTiles{ static_cast<float>(levelLayout.size()) };
	const float columnTiles{ static_cast<float>(levelLayout[0].length()) }; // every row has same amount of columns
	const glm::vec2 positionGrid{ 0.f, 3 * sizeTiles };
	const glm::vec2 sizeGrid{ columnTiles * sizeTiles, rowTiles * sizeTiles };

	auto grid = std::make_shared<GameObject>("grid");
	grid->AddComponent<Grid>(sizeGrid.x, sizeGrid.y, sizeTiles, positionGrid, levelLayout);

	scene.Add(grid);

	std::cout << "Grid creation sucessful : rows = " << std::to_string(rowTiles) << " columns = " << std::to_string(columnTiles) << "\n";
}

void dae::LevelManager::CreateWorldTiles(Scene& scene)
{
	// access grid data
	const auto gridObj{ scene.FindObject("grid") };
	auto grid{ gridObj->GetComponent<Grid>() };
	const auto gridCells{ gridObj->GetComponent<Grid>()->GetCells() };

	int tileNr{ 1 };

	for (const auto& cell : gridCells)
	{
		auto worldTile = std::make_shared<GameObject>("WorldTile" + std::to_string(tileNr++));
		worldTile->GetTransform()->SetPosition(static_cast<float>(cell.dstRect.x), static_cast<float>(cell.dstRect.y));
		worldTile->AddComponent<Tile>(cell.dstRect, grid, m_GameScale);

		if (cell.IsDug)
		{
			SDL_Rect tunnel{ 128, 0, 16,16 }; // offset.x, offset.y spritesize.w , spritesize.h
			worldTile->AddComponent<Sprite>("General Sprites.png", tunnel, m_GameScale);
			worldTile->AddComponent<SpriteRenderer>();
		}
		scene.Add(worldTile);
	}
}

void dae::LevelManager::CreatePlayer(Scene& scene, const GameMode& gameMode)
{
	switch (gameMode)
	{
	case dae::GameMode::SINGLEPLAYER:
		CreateSinglePlayer(scene);
		break;
	case dae::GameMode::CO_OP:
		break;
	case dae::GameMode::VERSUS:
		break;
	default:
		break;
	}


	
}

void dae::LevelManager::CreateEnemies(Scene& scene, const GameMode& /*gameMode*/)
{
	auto gridObj{ scene.FindObject("grid") };
	auto pGrid{ gridObj->GetComponent<Grid>() };

	for (int index{}; index < pGrid->GetPookaStartPoints().size(); index++)
	{
		auto pooka{ std::make_shared<GameObject>("pooka" + std::to_string(index+1)) };
		pooka->AddComponent<Enemy>(pGrid, index)->InitEnemy();
		scene.Add(pooka);
	}
}

void dae::LevelManager::CreateSinglePlayer(Scene& scene)
{
	auto gridObj{ scene.FindObject("grid") };
	auto pGrid{ gridObj->GetComponent<Grid>() };

	auto player{ std::make_shared<GameObject>("player") };
	player->AddComponent<Player>(pGrid)->InitPlayer();

	scene.Add(player);

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
		auto moveCommand{ std::make_shared<GridMoveCommand>(player.get(), speed, direction, pGrid) };
		controller->AttachCommandToButton(moveCommand, { button, ControllerInput::ButtonState::Pressed });
	}

	// thumbsticks controls
	auto button = ControllerInput::ControllerButtons::LeftThumbstick;
	auto pMoveCommandStick{ std::make_shared<GridMoveCommand>(player.get(), speed, controller->GetDirectionLeftThumbStick(), pGrid) };

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
		auto pMoveCommand = std::make_shared<dae::GridMoveCommand>(player.get(), speed, direction, pGrid);
		keyboard->AttachCommandToButton(pMoveCommand, keyPressed);
	}
}

void dae::LevelManager::SetupHUD(Scene& scene)
{
	// Get player object
	auto player = scene.FindObject("player");

	// Add lives display for player
	glm::vec2 posLives{ 0.f, 408.f };

	auto livesPlayer = std::make_shared<dae::GameObject>("livesPlayer");
	livesPlayer->GetTransform()->SetPosition(posLives);
	auto display = livesPlayer->AddComponent<LivesDisplayComponent>(player.get());
	display->InitializeLivesSprites();
	scene.Add(livesPlayer);

	// Add score display for player
	glm::vec2 posScore{ 220.f, 412.f };

	auto scorePlayer = std::make_shared<dae::GameObject>("ScorePlayer");
	scorePlayer->GetTransform()->SetPosition(posScore);
	scorePlayer->AddComponent<ScoreDisplayComponent>()->SetOwnerScore(player.get());
	scene.Add(scorePlayer);
}

void dae::LevelManager::CreateFPSObject(Scene& scene)
{
	glm::vec2 posFPS{ 150.f,20.f };
	SDL_Color color{ 255,0,0 };

	auto fpsCounter = std::make_shared<dae::GameObject>("fpsCounter");
	fpsCounter->GetTransform()->SetPosition(posFPS);
	fpsCounter->AddComponent<Texture>(""); // empty texture
	auto fpsComponent = fpsCounter->AddComponent<dae::FPSComponent>();
	fpsComponent->SetColor(color);
	scene.Add(fpsCounter);
}
