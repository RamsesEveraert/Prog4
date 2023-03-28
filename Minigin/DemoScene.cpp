#include "DemoScene.h"

// managers
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "GameObject.h"
#include "Scene.h"

// components
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "TrashCacheComponent.h"
#include "Transform.h"

// Commands

#include "MoveCommand.h"

using namespace dae;

void DemoScene::LoadDemoScene()
{
    // Create scene
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    CreateBackground(scene);
    CreateLogo(scene);
    CreateTextObject(scene);
    CreateFPSObject(scene);
	/*CreateRotatingObjects(scene);
	InputsExercice(scene);*/

}

void dae::DemoScene::CreateBackground(Scene& scene)
{
    auto background = std::make_shared<dae::GameObject>("background");
    background->AddComponent<dae::TextureComponent>()->SetTextureByPath("background.tga");
    background->AddComponent<dae::RenderComponent>();
    scene.Add(background);
}

void dae::DemoScene::CreateLogo(Scene& scene)
{
    auto logo = std::make_shared<dae::GameObject>("logo");
    logo->GetTransform()->SetPosition(glm::vec3{ 216,190,0 });
    logo->AddComponent<dae::TextureComponent>()->SetTextureByPath("logo.tga");
    logo->AddComponent<dae::RenderComponent>();
    scene.Add(logo);
}

void dae::DemoScene::CreateTextObject(Scene& scene)
{
    auto textObject = std::make_shared<dae::GameObject>("textObject");
    textObject->GetTransform()->SetPosition(glm::vec3{ 190,250,0 });
    textObject->AddComponent<dae::TextureComponent>();
    textObject->AddComponent<dae::TextComponent>()->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
    textObject->GetComponent<TextComponent>()->SetText("Programming 4:");
    textObject->AddComponent<dae::RenderComponent>();
    scene.Add(textObject);
}

void dae::DemoScene::CreateFPSObject(Scene& scene)
{
    auto fpsCounter = std::make_shared<dae::GameObject>("fpsCounter");
    fpsCounter->GetTransform()->SetPosition(glm::vec3{ 20,20,0 });
    fpsCounter->AddComponent<dae::TextureComponent>();
    fpsCounter->AddComponent<dae::TextComponent>()->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
    fpsCounter->GetComponent<TextComponent>()->SetText(" ");
    fpsCounter->AddComponent<dae::RenderComponent>();
    fpsCounter->AddComponent<dae::FPSComponent>();
    scene.Add(fpsCounter);
}

void dae::DemoScene::CreateRotatingObjects(Scene& scene)
{
	// test centerpoint

	auto centerPoint = std::make_shared<dae::GameObject>("centerPoint");
	centerPoint->GetTransform()->SetPosition(glm::vec3{ 300,300,0 });

	centerPoint->AddComponent<TextureComponent>()->SetTextureByPath("char1.png");
	centerPoint->AddComponent<RenderComponent>();

	scene.Add(centerPoint);

	// Rotating object 1 --> werkt niet?

	auto parentObject = std::make_shared<dae::GameObject>("ParentObject");
	parentObject->GetTransform()->SetPosition(glm::vec3{ 300,300, 0 });
    parentObject->AddComponent<TextureComponent>()->SetTextureByPath("char1.png");
    parentObject->AddComponent<RotatorComponent>()->SetCenterPoint(glm::vec3{ 300,300, 0 });
    parentObject->GetComponent<RotatorComponent>()->SetRadius(100.f);
    parentObject->GetComponent<RotatorComponent>()->SetRotationSpeed(1.f);
    parentObject->AddComponent<RenderComponent>();

	scene.Add(parentObject);

	// Rotating object 2

	auto childObject = std::make_shared<dae::GameObject>("childObject");
    childObject->AddComponent<TextureComponent>()->SetTextureByPath("char2.png");
    childObject->AddComponent<RotatorComponent>();
    childObject->SetParent(parentObject.get(),true);
    childObject->GetComponent<RotatorComponent>()->SetCenterPoint(parentObject->GetTransform()->GetWorldPosition());
    childObject->GetComponent<RotatorComponent>()->SetRadius(25.f);
    childObject->GetComponent<RotatorComponent>()->SetRotationSpeed(-4.f);
    childObject->AddComponent<RenderComponent>();

	scene.Add(childObject);
}

void dae::DemoScene::InputsExercice(Scene& scene)
{
    auto player1 = std::make_shared<dae::GameObject>("p1");
    player1->GetTransform()->SetPosition(glm::vec3{ 300,300,0 });
    player1->AddComponent<TextureComponent>()->SetTextureByPath("char1.png");
    player1->AddComponent<RenderComponent>();

	//*** commands controller ***//

	auto controller = dae::InputManager::GetInstance().AddController();
	auto player = player1.get();
	std::vector<std::pair<dae::ControllerInput::ControllerButtons, glm::vec3>> buttonDirections = {
		{ dae::ControllerInput::ControllerButtons::DPadUp, {0.f, -1.f, 0.f} },
		{ dae::ControllerInput::ControllerButtons::DPadDown, {0.f, 1.f, 0.f} },
		{ dae::ControllerInput::ControllerButtons::DPadRight, {1.f, 0.f, 0.f} },
		{ dae::ControllerInput::ControllerButtons::DPadLeft, {-1.f, 0.f, 0.f} }
	};

	for (auto& buttonDirection : buttonDirections)
	{
		auto button = std::make_pair(buttonDirection.first, dae::ControllerInput::ButtonState::Pressed);
		auto direction = buttonDirection.second;
		float speed{ 40.f };

		auto pMoveCommand = std::make_shared<dae::MoveCommand>(player, speed, direction);
		controller->AttachCommandToButton(pMoveCommand, button);
	}	

	scene.Add(player1);


	//*** commands keyboard ***//

	auto player2 = std::make_shared<GameObject>("p2");
	player2->GetTransform()->SetPosition(glm::vec3{ 350,350,0 });
	player2->AddComponent<TextureComponent>()->SetTextureByPath("char2.png");
	player2->AddComponent<RenderComponent>();

	player = player2.get();
	auto keyboard = dae::InputManager::GetInstance().GetKeyboard();

	std::vector<std::pair<SDL_Scancode, glm::vec3>> keyDirections = {
	{ SDL_SCANCODE_W, {0.f, -1.f, 0.f} },
	{ SDL_SCANCODE_S, {0.f, 1.f, 0.f} },
	{ SDL_SCANCODE_D, {1.f, 0.f, 0.f} },
	{ SDL_SCANCODE_A, {-1.f, 0.f, 0.f} }
	};

	for (auto& keyDirection : keyDirections)
	{
		auto keyPressed = std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Pressed);
		auto keyDown = std::make_pair(keyDirection.first, dae::KeyboardInput::KeyState::Down);
		auto direction = keyDirection.second;
		float speed{ 80.f };
		auto pMoveCommand = std::make_shared<dae::MoveCommand>(player, speed, direction);
		keyboard->AttachCommandToButton(pMoveCommand, keyPressed);
	}
	scene.Add(player2);
}