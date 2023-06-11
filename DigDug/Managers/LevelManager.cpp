#include "LevelManager.h"

// Singletons
#include "SceneManager.h"
#include "TextureRenderer.h"
#include "EventHandler.h"
#include "InputManager.h"

// GameAssets
#include "GameObject.h"
#include "Event.h"
#include "Texture2D.h"


// Components
#include "Sprite.h"
#include "Score.h"
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
#include "InstructionsComponent.h"

#include "../Pooka.h"

// Commands
#include "GridMoveCommand.h"
#include "../NextLevelCommand.h"

// Other includes
#include <fstream>
#include <sstream>
#include <SDL.h>

void dae::LevelManager::LoadStartScreen()
{
	EventHandler::GetInstance().AddListener("NextLevel", [&](const dae::Event& event) { StartNextLevel(event); });
	EventHandler::GetInstance().AddListener("PlayerDied", [&](const dae::Event& event) { LoadGameOver(event); });
	auto& scene = dae::SceneManager::GetInstance().CreateScene("StartOptions");

	//****** instruction *****//////

	auto instructions = std::make_shared<dae::GameObject>("Instructions");
	instructions->AddComponent<InstructionsComponent>();
	scene.Add(instructions);


	//********** Game Window *************//

	CreateSchoolBackground(scene);
	CreateSchoolLogo(scene);
	CreateGameLogo(scene);

	//********** Game Modes  *************//

	CreateSinglePlayerButton(scene);
	Create_Co_Op_Button(scene); 
	CreateVersusButton(scene); // Todo implement in Game
	
}

void dae::LevelManager::LoadLevel(Scene& scene, GameMode mode, int nrLevel)
{
	// Reset Level
	m_GameMode = mode;
	m_NrLevel = nrLevel;

	ResetLevel(&scene);

	// start new LevelScene
	auto& level = dae::SceneManager::GetInstance().CreateScene("Level");
	m_CurrentScene = &level;

	// parse data from file
	std::ifstream levelFile{ GetLevelPath(m_NrLevel)};
	std::vector<std::string> levelLayout{GetLevelLayout(levelFile)};
	
	// Create Background
	CreateLevelBackground(level, nrLevel);

	// Create Grid
	CreateGrid(level, levelLayout);

	// Create world tiles
	CreateWorldTiles(level);

	// Create Players
	CreatePlayer(level, mode);

	// Create Enemies
	if(m_GameMode != GameMode::VERSUS) CreateEnemies(level, mode);

	// Setup HUD
	SetupHUD(level, mode);

	// Add (temporary) fps counter
	CreateFPSObject(level);

}

void dae::LevelManager::StartNextLevel(const Event& /*event*/)
{
	// Crashes: todo fix button life time -> new level = nullptr /dangling pointers  issue (?)z

	int nextLevel{ m_NrLevel >= 3 ? 1 : m_NrLevel + 1 };
	LoadLevel(*m_CurrentScene, m_GameMode, nextLevel);
}



void dae::LevelManager::LoadGameOver(const Event& event)
{
	auto player{ m_CurrentScene->FindObject("P1") };

	if (player.get() == nullptr)
	{
		std::cout << "player is nullptr \n";
	}
	else
	{
		std::string ownerName{};
		for (const auto& data : event.data)
		{
			if (data.type() == typeid(std::string))
			{
				ownerName = std::any_cast<std::string>(data);
			}
		}

		//if (player.get()->GetObjectName() != ownerName) return; // not for this player

		auto& scene = dae::SceneManager::GetInstance().CreateScene("GameOver");

		if (m_CurrentScene)
		{
			std::cout << "currentscene isn't nullptr \n";
			ResetLevel(m_CurrentScene);
		}
		else
		{
			std::cout << "currentscene is nullptr \n";
		}

		// Debug output
		std::cout << "LoadGameOver called\n";

		CreateScoreDisplay(scene, player.get());

		CreateSchoolBackground(scene);
		CreateGameOverLogo(scene);
		CreateContinueButton(scene);
	}

	// Debug output
	std::cout << "LoadGameOver finished\n";
}

void dae::LevelManager::ResetLevel(Scene* scene)
{
	dae::SceneManager::GetInstance().RemoveScene(scene);
}

void dae::LevelManager::CreateLevelBackground(Scene& scene, int nrLevel)
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

	std::cout << "grid added";
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
		Create_Co_Op_Players(scene);
		break;
	case dae::GameMode::VERSUS:
		Create_Versus_Players(scene);
		break;
	}


	
}

void dae::LevelManager::CreateEnemies(Scene& scene, const GameMode& /*gameMode*/)
{
	auto gridObj{ scene.FindObject("grid") };
	auto pGrid{ gridObj->GetComponent<Grid>() };

	auto p1{ scene.FindObject("P1") };

	for (int index{}; index < static_cast<int>( pGrid->GetPookaStartPoints().size()); index++)
	{
		auto pooka{ std::make_shared<GameObject>("pooka" + std::to_string(index+1)) };
		pooka->AddComponent<Pooka>(p1.get(), pGrid, index)->Initialize();
		scene.Add(pooka);
	}
}

void dae::LevelManager::CreateSinglePlayer(Scene& scene)
{
	auto gridObj{ scene.FindObject("grid") };
	auto pGrid{ gridObj->GetComponent<Grid>() };

	auto player{ std::make_shared<GameObject>("P1") };
	player->AddComponent<Player>(pGrid)->InitPlayer(true);

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
		auto direction = keyDirection.second;
		auto pMoveCommand = std::make_shared<dae::GridMoveCommand>(player.get(), speed, direction, pGrid);
		keyboard->AttachCommandToButton(pMoveCommand, keyPressed);
	}

	// add skip level button
	auto keyPressed = std::make_pair(SDL_SCANCODE_N, dae::KeyboardInput::KeyState::Pressed);
	if(!m_NextLevelCommand) m_NextLevelCommand = std::make_shared<dae::NextLevelCommand>();
	keyboard->AttachCommandToButton(m_NextLevelCommand, keyPressed);

}

void dae::LevelManager::Create_Co_Op_Players(Scene& scene)
{
	// get grid information 

	auto gridObj{ scene.FindObject("grid") };
	auto pGrid{ gridObj->GetComponent<Grid>() };

	//create p1
	auto p1{ std::make_shared<GameObject>("P1") };
	p1->AddComponent<Player>(pGrid)->InitPlayer(true);

	scene.Add(p1);

	// create p2
	auto p2{ std::make_shared<GameObject>("P2") };
	p2->AddComponent<Player>(pGrid)->InitPlayer(false);

	scene.Add(p2);

	// add controller to player 1

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
		auto moveCommand{ std::make_shared<GridMoveCommand>(p1.get(), speed, direction, pGrid) };
		controller->AttachCommandToButton(moveCommand, { button, ControllerInput::ButtonState::Pressed });
	}

	// thumbsticks controls
	auto button = ControllerInput::ControllerButtons::LeftThumbstick;
	auto pMoveCommandStick{ std::make_shared<GridMoveCommand>(p1.get(), speed, controller->GetDirectionLeftThumbStick(), pGrid) };

	controller->AttachCommandToThumbStick(pMoveCommandStick, button);

	// add keyboard to p2

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
		auto pMoveCommand = std::make_shared<dae::GridMoveCommand>(p2.get(), speed, direction, pGrid);
		keyboard->AttachCommandToButton(pMoveCommand, keyPressed);
	}
}

void dae::LevelManager::Create_Versus_Players(Scene& /*scene*/)
{
}

std::string dae::LevelManager::GetLevelPath(int nrLevel)
{
	std::stringstream levelPath;
	levelPath << "../Data/";

	if (m_GameMode == GameMode::SINGLEPLAYER) levelPath << "SinglePlayer/";
	else if (m_GameMode == GameMode::CO_OP) levelPath << "CO_OP/";
	else if (m_GameMode == GameMode::VERSUS) levelPath << "Versus/";

	levelPath << "level" << nrLevel << ".txt";

	return levelPath.str();
}

std::vector<std::string> dae::LevelManager::GetLevelLayout(std::ifstream& levelFile)
{
	if (!levelFile.is_open()) std::cout << "levelLayout can't be found \n";

	std::vector<std::string> levelLayout{}; // stores a line in ea index
	std::string line;

	while (std::getline(levelFile, line))
	{
		levelLayout.push_back(line); // pushback: copy needed
	}

	levelFile.close();

	return levelLayout;
}

void dae::LevelManager::CreateSingplayerHUD(Scene& scene, GameObject* p1)
{
	// Add lives display for player 1
	glm::vec2 posLives{ 0.f, 408.f };

	auto livesPlayer1 = std::make_shared<dae::GameObject>("livesPlayer");
	livesPlayer1->GetTransform()->SetPosition(posLives);
	auto display = livesPlayer1->AddComponent<LivesDisplayComponent>(p1, true);
	display->InitializeLivesSprites();
	scene.Add(livesPlayer1);

	// Add score display for player 1
	glm::vec2 posScore{ 200.f, 412.f };

	auto scorePlayer = std::make_shared<dae::GameObject>("ScorePlayer");
	scorePlayer->GetTransform()->SetPosition(posScore);
	scorePlayer->AddComponent<ScoreDisplayComponent>()->ShowScore(p1);
	scene.Add(scorePlayer);
}

void dae::LevelManager::Create_CO_OP_HUD(Scene& scene, GameObject* p1, GameObject* p2)
{
	// Add lives display for player 1
	glm::vec2 posLives{ 0.f, 408.f };

	auto livesPlayer1 = std::make_shared<dae::GameObject>("lives P1");
	livesPlayer1->GetTransform()->SetPosition(posLives);
	auto display = livesPlayer1->AddComponent<LivesDisplayComponent>(p1, true);
	display->InitializeLivesSprites();
	scene.Add(livesPlayer1);

	// Add lives display for player 2
	glm::vec2 posLives2{ 210.f, 408.f };

	auto livesPlayer2 = std::make_shared<dae::GameObject>("lives P2");
	livesPlayer2->GetTransform()->SetPosition(posLives2);
	auto display2 = livesPlayer2->AddComponent<LivesDisplayComponent>(p2, false);
	display2->InitializeLivesSprites();
	scene.Add(livesPlayer2);

}

void dae::LevelManager::CreateVersusHUD(Scene& /*scene*/, GameObject* /*p1*/, GameObject* /*p2*/)
{
}

void dae::LevelManager::SetupHUD(Scene& scene, const GameMode& gameMode)
{

	// Get P1 & P2
	auto p1 = scene.FindObject("P1");
	auto p2 = scene.FindObject("P2");

	// Create HUD
	switch (gameMode)
	{
	case dae::GameMode::SINGLEPLAYER:
		CreateSingplayerHUD(scene, p1.get());
		break;
	case dae::GameMode::CO_OP:
		Create_CO_OP_HUD(scene, p1.get(), p2.get());
		break;
	case dae::GameMode::VERSUS:
		CreateVersusHUD(scene, p1.get(), p2.get());
		break;
	default:
		break;
	}
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

void dae::LevelManager::CreateGameLogo(Scene& scene)
{
	auto gameLogo = std::make_shared<dae::GameObject>("gameLogo");
	gameLogo->GetTransform()->SetPosition(glm::vec2{ 65.f,135.f });
	gameLogo->AddComponent<Texture>("GameLogo.png");
	gameLogo->AddComponent<TextureRenderer>();
	scene.Add(gameLogo);
}

void dae::LevelManager::CreateGameOverLogo(Scene& scene)
{
	auto gameOverLogo = std::make_shared<dae::GameObject>("gameOverLogo");
	gameOverLogo->GetTransform()->SetPosition(glm::vec2{ 65.f,180.f });
	gameOverLogo->AddComponent<Texture>("gameOver.png");
	gameOverLogo->AddComponent<TextureRenderer>();
	scene.Add(gameOverLogo);
}

void dae::LevelManager::CreateScoreDisplay(Scene& scene, GameObject* player)
{

	glm::vec2 posScore{ 220.f, 412.f };

	auto scorePlayer = std::make_shared<dae::GameObject>("ScorePlayer");
	scorePlayer->GetTransform()->SetPosition(posScore);
	scorePlayer->AddComponent<ScoreDisplayComponent>()->ShowHighScore(player);
	scene.Add(scorePlayer);
}

void dae::LevelManager::CreateSchoolBackground(Scene& scene)
{
	auto background = std::make_shared<dae::GameObject>("background");
	background->AddComponent<Texture>("background.tga");
	background->AddComponent<TextureRenderer>();
	scene.Add(background);
}

void dae::LevelManager::CreateSchoolLogo(Scene& scene)
{
	auto logo = std::make_shared<dae::GameObject>("logo");
	logo->GetTransform()->SetPosition(glm::vec2{ 65.f,40.f });
	logo->AddComponent<Texture>("logo.tga");
	logo->AddComponent<TextureRenderer>();
	scene.Add(logo);
}

void dae::LevelManager::CreateSinglePlayerButton(Scene& scene)
{
	auto singlePlayer = std::make_shared<dae::GameObject>("SinglePlayer");
	glm::vec2 buttonPosition{ 95.f,285.f };
	singlePlayer->GetTransform()->SetPosition(buttonPosition);
	singlePlayer->AddComponent<Texture>("SinglePlayer.png");
	singlePlayer->AddComponent<TextureRenderer>();

	auto onClick = [&]() { LevelManager::GetInstance().LoadLevel(scene, GameMode::SINGLEPLAYER, 1); };
	const glm::vec2 sizeButton{ 150.f, 23.f };
	singlePlayer->AddComponent<Button>(buttonPosition, sizeButton, onClick);

	scene.Add(singlePlayer);
}

void dae::LevelManager::Create_Co_Op_Button(Scene& scene)
{
	auto co_op = std::make_shared<dae::GameObject>("co_op");
	glm::vec2 buttonPosition{ 95.f, 315.f };
	co_op->GetTransform()->SetPosition(buttonPosition);
	co_op->AddComponent<Texture>("co_op.png");
	co_op->AddComponent<TextureRenderer>();

	auto onClick = [&]() { LevelManager::GetInstance().LoadLevel(scene, GameMode::CO_OP, 1); };
	const glm::vec2 sizeButton{ 150.f, 23.f };
	co_op->AddComponent<Button>(buttonPosition, sizeButton, onClick);

	scene.Add(co_op);
}

void dae::LevelManager::CreateVersusButton(Scene& scene)
{
	auto versus = std::make_shared<dae::GameObject>("versus");
	versus->GetTransform()->SetPosition(glm::vec2{ 95.f, 345.f });
	versus->AddComponent<Texture>("Versus.png");
	versus->AddComponent<TextureRenderer>();
	scene.Add(versus);
}

void dae::LevelManager::CreateContinueButton(Scene& scene)
{
	const auto continueButton = std::make_shared<dae::GameObject>("continue");
	const auto buttonPosition{ glm::vec2{ 95.f, 250.f } };

	continueButton->GetTransform()->SetPosition(buttonPosition);
	continueButton->AddComponent<Texture>("Continue.png");
	continueButton->AddComponent<TextureRenderer>();

	auto onClickSinglePlayer = [&]() { LevelManager::GetInstance().LoadStartScreen(); };
	const glm::vec2 sizeButton{ 150.f, 23.f };
	continueButton->AddComponent<Button>(buttonPosition, sizeButton, onClickSinglePlayer);

	scene.Add(continueButton);
}
