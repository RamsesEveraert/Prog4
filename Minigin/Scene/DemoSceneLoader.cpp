#include "DemoSceneLoader.h"

// managers
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "GameObject.h"
#include "Scene.h"

// components
#include "Texture.h"
#include "RenderComponent.h"
#include "Text.h"
#include "FPSComponent.h"
#include "Transform.h"

// Commands

#include "HealthCommand.h"
#include "ScoreCommand.h"

using namespace dae;

dae::DemoSceneLoader::DemoSceneLoader()
{
	// Create scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	CreateBackground(scene);
	CreateLogo(scene);
	CreateTextObject(scene);
	CreateFPSObject(scene);
	//InputsExercice(scene);
	/*EventExercice(scene);*/
}

void dae::DemoSceneLoader::CreateBackground(Scene& scene)
{
    auto background = std::make_shared<dae::GameObject>("background");
	background->AddComponent<dae::Texture>("background.tga");
    background->AddComponent<dae::RenderComponent>();
    scene.Add(background);
}

void dae::DemoSceneLoader::CreateLogo(Scene& scene)
{
    auto logo = std::make_shared<dae::GameObject>("logo");
    logo->GetTransform()->SetPosition(glm::vec2{ 216,190 });
    logo->AddComponent<dae::Texture>("logo.tga");
    logo->AddComponent<dae::RenderComponent>();
    scene.Add(logo);
}

void dae::DemoSceneLoader::CreateTextObject(Scene& scene)
{
    auto textObject = std::make_shared<dae::GameObject>("textObject");
    textObject->GetTransform()->SetPosition(glm::vec2{ 190,250 });
    textObject->AddComponent<dae::Texture>("");
    textObject->AddComponent<dae::Text>()->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
    textObject->GetComponent<Text>()->SetText("Programming 4:");
    textObject->AddComponent<dae::RenderComponent>();
    scene.Add(textObject);
}

void dae::DemoSceneLoader::CreateFPSObject(Scene& scene)
{
    auto fpsCounter = std::make_shared<dae::GameObject>("fpsCounter");
    fpsCounter->GetTransform()->SetPosition(glm::vec2{ 20,20 });
    fpsCounter->AddComponent<dae::Texture>("");
    fpsCounter->AddComponent<dae::Text>()->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
    fpsCounter->GetComponent<Text>()->SetText(" ");
    fpsCounter->AddComponent<dae::RenderComponent>();
    fpsCounter->AddComponent<dae::FPSComponent>();
    scene.Add(fpsCounter);
}


//void dae::DemoSceneLoader::InputsExercice(Scene& scene)
//{
//    auto player1 = std::make_shared<dae::GameObject>("player1");
//    player1->GetTransform()->SetPosition(glm::vec2{ 300,300 });
//    player1->AddComponent<Texture>("char1.png");
//    player1->AddComponent<RenderComponent>();
//
//	//*** commands controller ***//
//
//	auto controller = dae::InputManager::GetInstance().AddController();
//	auto player = player1.get();
//
//	//dpad controls
//
//	/*std::vector<std::pair<dae::ControllerInput::ControllerButtons, glm::vec2>> buttonDirections = {
//		{ dae::ControllerInput::ControllerButtons::DPadUp, {0.f, -1.f} },
//		{ dae::ControllerInput::ControllerButtons::DPadDown, {0.f, 1.f} },
//		{ dae::ControllerInput::ControllerButtons::DPadRight, {1.f, 0.f} },
//		{ dae::ControllerInput::ControllerButtons::DPadLeft, {-1.f, 0.f} }
//	};
//
//	for (auto& buttonDirection : buttonDirections)
//	{
//		auto button = std::make_pair(buttonDirection.first, dae::ControllerInput::ButtonState::Pressed);
//		auto direction = buttonDirection.second;
//		float speed{ 40.f };
//
//		auto pMoveCommand = std::make_shared<dae::MoveCommand>(player, speed, direction);
//		controller->AttachCommandToButton(pMoveCommand, button);
//	}	*/
//
//	// thumbsticks controls
//	/*auto button = ControllerInput::ControllerButtons::LeftThumbstick;
//	float stickSpeed{ 40.f };*/
//	//auto pMoveCommandStick = std::make_shared<dae::MoveStickCommand>(player, stickSpeed, controller->GetDirectionLeftThumbStick());
//
//	//controller->AttachCommandToThumbStick(pMoveCommandStick, button);
//
//	// trigger controls
//
//	//button = ControllerInput::ControllerButtons::RightBumper;
//	//auto pMoveCommandTrigger = std::make_shared<dae::MoveCommand>(player, stickSpeed, glm::vec2{0,0}); // test purpose only
//	//controller->AttachCommandToTrigger(pMoveCommandTrigger, button);
//	//button = ControllerInput::ControllerButtons::LeftBumper;
//	//pMoveCommandTrigger = std::make_shared<dae::MoveCommand>(player, stickSpeed, glm::vec2{ 0,0 }); // test purpose only
//	//controller->AttachCommandToTrigger(pMoveCommandStick, button);
//
//	scene.Add(player1);
//
//
//	//*** commands keyboard ***//
//
//	auto player2 = std::make_shared<GameObject>("player2");
//	player2->GetTransform()->SetPosition(glm::vec2{ 350,350 });
//	player2->AddComponent<Texture>("char2.png");
//	player2->AddComponent<RenderComponent>();
//
//	player = player2.get();
//	auto keyboard = dae::InputManager::GetInstance().AddKeyboard();
//
//	std::vector<std::pair<SDL_Scancode, glm::vec2>> keyDirections = {
//	{ SDL_SCANCODE_W, {0.f, -1.f} },
//	{ SDL_SCANCODE_S, {0.f, 1.f} },
//	{ SDL_SCANCODE_D, {1.f, 0.f} },
//	{ SDL_SCANCODE_A, {-1.f, 0.f} }
//	};
//
//	for (auto& keyDirection : keyDirections)
//	{
//		auto keyPressed = std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Pressed);
//		auto keyDown = std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Down);
//		auto direction = keyDirection.second;
//		float speed{ 80.f };
//		auto pMoveCommand = std::make_shared<dae::MoveCommand>(player, speed, direction);
//		keyboard->AttachCommandToButton(pMoveCommand, keyPressed);
//	}
//	scene.Add(player2);
//}

//void dae::DemoSceneLoader::EventExercice(Scene& scene)
//{

	//// instructions

	//auto instructions = std::make_shared<GameObject>("Instructions");
	//instructions->AddComponent<InstructionsComponent>();

	//scene.Add(instructions);

	////******* player 1 **********//

	//auto player1 = std::make_shared<GameObject>("player 1");
	//player1->GetTransform()->SetPosition(glm::vec2{ 300,300 });
	//player1->AddComponent<TextureComponent>()->SetTextureByPath("char1.png");
	//player1->AddComponent<RenderComponent>();

	//// Add controller inputs

	//auto controller = InputManager::GetInstance().AddController(); // specific keyboard and controller for ea player
	//auto keyboard = InputManager::GetInstance().AddKeyboard();
	//float stickSpeed{ 40.f };
	//auto pMoveCommandStick = std::make_shared<MoveStickCommand>(player1.get(), stickSpeed, controller->GetDirectionLeftThumbStick());
	//controller->AttachCommandToThumbStick(pMoveCommandStick, ControllerInput::ControllerButtons::LeftThumbstick);

	//int playerIdx = 0;

	//auto scoreCommand = std::make_shared<ScoreCommand>(player1.get(), playerIdx, ScoreCommand::InputType::Controller);
	//auto healthCommand = std::make_shared<HealthCommand>(player1.get(), playerIdx, HealthCommand::InputType::Controller);
	//controller->AttachCommandToButton(scoreCommand, std::make_pair(ControllerInput::ControllerButtons::ButtonB, ControllerInput::ButtonState::Pressed));
	//controller->AttachCommandToButton(scoreCommand, std::make_pair(ControllerInput::ControllerButtons::ButtonX, ControllerInput::ButtonState::Pressed));
	//controller->AttachCommandToButton(healthCommand, std::make_pair(ControllerInput::ControllerButtons::ButtonA, ControllerInput::ButtonState::Pressed));
	//controller->AttachCommandToButton(healthCommand, std::make_pair(ControllerInput::ControllerButtons::ButtonY, ControllerInput::ButtonState::Pressed));

	//scene.Add(player1);

	//// add lives display P1

	//auto livesPlayer1 = std::make_shared<dae::GameObject>("livesPlayer1");
	//livesPlayer1->GetTransform()->SetPosition(glm::vec2{ 10,300 });
	//auto livesDisplayComponent = livesPlayer1->AddComponent<LivesDisplayComponent>();
	//livesDisplayComponent->SetOwnerLives(player1.get());

	//livesPlayer1->AddComponent<RenderComponent>();

	//scene.Add(livesPlayer1);

	//// add Score Display P1

	//auto scorePlayer1 = std::make_shared<dae::GameObject>("ScorePlayer1");
	//scorePlayer1->GetTransform()->SetPosition(glm::vec2{ 10,320 });
	//auto scoreDisplayComponent = scorePlayer1->AddComponent<ScoreDisplayComponent>();
	//scoreDisplayComponent->SetOwnerScore(player1.get());

	//scorePlayer1->AddComponent<RenderComponent>();

	//scene.Add(scorePlayer1);

	////******* player 2 **********//

	//auto player2 = std::make_shared<dae::GameObject>("player2");
	//player2->GetTransform()->SetPosition(glm::vec2{ 350,350 });
	//player2->AddComponent<TextureComponent>()->SetTextureByPath("char2.png");
	//player2->AddComponent<RenderComponent>();

	//scene.Add(player2);

	//// Add Keyboard inputs

	//controller = InputManager::GetInstance().AddController();
	//keyboard = InputManager::GetInstance().AddKeyboard();

	//KeyboardInput::KeyboardKey keyLeft(SDL_SCANCODE_LEFT, KeyboardInput::KeyState::Down);
	//KeyboardInput::KeyboardKey keyRight(SDL_SCANCODE_RIGHT, KeyboardInput::KeyState::Down);
	//KeyboardInput::KeyboardKey keyUp(SDL_SCANCODE_UP, KeyboardInput::KeyState::Down);
	//KeyboardInput::KeyboardKey keyDown(SDL_SCANCODE_DOWN, KeyboardInput::KeyState::Down);

	//playerIdx = 1;

	//auto scoreCommandP2 = std::make_shared<ScoreCommand>(player2.get(), playerIdx, ScoreCommand::InputType::Keyboard);
	//auto healthCommandP2 = std::make_shared<HealthCommand>(player2.get(), playerIdx, HealthCommand::InputType::Keyboard);

	//keyboard->AttachCommandToButton(scoreCommandP2, keyLeft);
	//keyboard->AttachCommandToButton(scoreCommandP2, keyRight);
	//keyboard->AttachCommandToButton(healthCommandP2, keyUp);
	//keyboard->AttachCommandToButton(healthCommandP2, keyDown);

	//std::vector<std::pair<SDL_Scancode, glm::vec2>> keyDirections = {
	//	{ SDL_SCANCODE_W, {0.f, -1.f} },
	//	{ SDL_SCANCODE_S, {0.f, 1.f} },
	//	{ SDL_SCANCODE_D, {1.f, 0.f} },
	//	{ SDL_SCANCODE_A, {-1.f, 0.f} }
	//};

	//for (auto& keyDirection : keyDirections)
	//{
	//	auto direction = keyDirection.second;
	//	float speed{ 80.f };
	//	auto pMoveCommand = std::make_shared<dae::MoveCommand>(player2.get(), speed, direction);
	//	keyboard->AttachCommandToButton(pMoveCommand, std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Pressed));
	//}

	//// add lives display P2

	//auto livesPlayer2 = std::make_shared<dae::GameObject>("livesPlayer2");
	//livesPlayer2->GetTransform()->SetPosition(glm::vec2{ 10,380 });
	//livesDisplayComponent = livesPlayer2->AddComponent<LivesDisplayComponent>();
	//livesDisplayComponent->SetOwnerLives(player2.get());

	//livesPlayer2->AddComponent<RenderComponent>();

	//scene.Add(livesPlayer2);

	//// add Score Display P2

	//auto scorePlayer2 = std::make_shared<dae::GameObject>("ScorePlayer2");
	//scorePlayer2->GetTransform()->SetPosition(glm::vec2{ 10,400 });
	//scoreDisplayComponent = scorePlayer2->AddComponent<ScoreDisplayComponent>();
	//scoreDisplayComponent->SetOwnerScore(player2.get());

	//scorePlayer2->AddComponent<RenderComponent>();
	//scene.Add(scorePlayer2);

//}