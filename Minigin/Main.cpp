#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include <glm/glm.hpp>

#include <iostream>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"

#include "GameObject.h"

#include "MoveCommand.h"


#include "TextComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "TrashCacheComponent.h"

#include "DebugComponent.h"

using namespace dae;

void load()
{
	//scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
		

	// background

	auto background = std::make_shared<dae::GameObject>("background");
	background->SetPosition(glm::vec3{ 0,0,0 });

	auto textureComponent = std::make_shared<dae::TextureComponent>(background, "background.tga");
	background->AddComponent<dae::TextureComponent>(textureComponent);

	auto renderComponent = std::make_shared<dae::RenderComponent>(background);
	background->AddComponent<dae::RenderComponent>(renderComponent);
	
	scene.Add(background);

	// logo

	auto logo = std::make_shared<dae::GameObject>("logo");
	logo->SetPosition(glm::vec3{ 216,190,0 });

	textureComponent = std::make_shared<dae::TextureComponent>(logo, "logo.tga");
	logo->AddComponent<dae::TextureComponent>(textureComponent);
	
	renderComponent = std::make_shared<dae::RenderComponent>(logo);
	logo->AddComponent<dae::RenderComponent>(renderComponent);	

	scene.Add(logo);


	// textobject

	auto textObject = std::make_shared<dae::GameObject>("textObject");
	textObject->SetPosition(glm::vec3{ 190,250,0 });
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	textureComponent = std::make_shared<dae::TextureComponent>(textObject, ""); // empty string used as null
	textObject->AddComponent<dae::TextureComponent>(textureComponent);

	auto textComponent = std::make_shared<dae::TextComponent>(textObject, "Programming 4: ", font);
	textObject->AddComponent<dae::TextComponent>(textComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(textObject);
	textObject->AddComponent<dae::RenderComponent>(renderComponent);	

	scene.Add(textObject);

	// FPSobject

	auto fpsCounter = std::make_shared<dae::GameObject>("fpsCounter");
	fpsCounter->SetPosition(glm::vec3{ 20,20,0 });
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	textureComponent = std::make_shared<dae::TextureComponent>(fpsCounter, "");// empty string used as null
	fpsCounter->AddComponent<dae::TextureComponent>(textureComponent);

	textComponent = std::make_shared<dae::TextComponent>(fpsCounter, " ", font); 
	fpsCounter->AddComponent<dae::TextComponent>(textComponent);
	
	renderComponent = std::make_shared<dae::RenderComponent>(fpsCounter);
	fpsCounter->AddComponent<dae::RenderComponent>(renderComponent);

	auto fpsComponent = std::make_shared<dae::FPSComponent>(fpsCounter);
	fpsCounter->AddComponent<dae::FPSComponent>(fpsComponent);	

	scene.Add(fpsCounter);

	// test centerpoint

	/*auto centerPoint = std::make_shared<dae::GameObject>("centerPoint");
	centerPoint->SetPosition(glm::vec3{ 300,300,0 });

	textureComponent = std::make_shared<dae::TextureComponent>(centerPoint, "char1.png");
	centerPoint->AddComponent<dae::TextureComponent>(textureComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(centerPoint);
	centerPoint->AddComponent<dae::RenderComponent>(renderComponent);

	scene.Add(centerPoint);*/

	// Rotating object 1

	/*auto parentObject = std::make_shared<dae::GameObject>("ParentObject");
	parentObject->SetPosition(glm::vec3{ 300,300, 0 });

	textureComponent = std::make_shared<dae::TextureComponent>(parentObject, "char1.png");
	parentObject->AddComponent<dae::TextureComponent>(textureComponent);

	auto rotatorComponent = std::make_shared<dae::RotatorComponent>(parentObject, glm::vec3{ 300,300, 0 });
	parentObject->AddComponent<dae::RotatorComponent>(rotatorComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(parentObject);
	parentObject->AddComponent<dae::RenderComponent>(renderComponent);

	parentObject.get()->GetComponent<dae::RotatorComponent>()->SetRadius(100.f);
	parentObject.get()->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(1.f);

	scene.Add(parentObject);*/

	// Rotating object 2

	/*auto childObject = std::make_shared<dae::GameObject>("childObject");

	textureComponent = std::make_shared<dae::TextureComponent>(childObject, "char2.png");
	childObject->AddComponent<dae::TextureComponent>(textureComponent);

	rotatorComponent = std::make_shared<dae::RotatorComponent>(childObject);
	childObject->AddComponent<dae::RotatorComponent>(rotatorComponent);

	childObject->SetParent(parentObject.get(), true);

	childObject.get()->GetComponent<dae::RotatorComponent>()->SetCenterPoint(parentObject->GetWorldPosition());
	childObject.get()->GetComponent<dae::RotatorComponent>()->SetRadius(25.f);
	childObject.get()->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(-4.f);

	renderComponent = std::make_shared<dae::RenderComponent>(childObject);
	childObject->AddComponent<dae::RenderComponent>(renderComponent);

	scene.Add(childObject);*/

	//// trash the cache 

	//auto plot1 = std::make_shared<dae::GameObject>();
	//auto plotComponent = std::make_shared<dae::TrashCacheComponent>(plot1);
	//plot1->AddComponent<dae::TrashCacheComponent>(plotComponent);

	float speed{ 40.f };
	auto player1 = std::make_shared<dae::GameObject>("p1");
	player1->SetPosition(glm::vec3{ 300,300,0 });

	textureComponent = std::make_shared<dae::TextureComponent>(player1, "char1.png");
	player1->AddComponent<dae::TextureComponent>(textureComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(player1);
	player1->AddComponent<dae::RenderComponent>(renderComponent);

	//*** commands controller ***//

	auto controller1 = dae::InputManager::GetInstance().AddController();
	auto player = player1.get();
	std::vector<std::pair<dae::GameController::ControllerButtons, glm::vec3>> buttonDirections = {
		{ dae::GameController::ControllerButtons::DPadUp, {0.f, -1.f, 0.f} },
		{ dae::GameController::ControllerButtons::DPadDown, {0.f, 1.f, 0.f} },
		{ dae::GameController::ControllerButtons::DPadRight, {1.f, 0.f, 0.f} },
		{ dae::GameController::ControllerButtons::DPadLeft, {-1.f, 0.f, 0.f} }
	};

	for (auto& buttonDirection : buttonDirections)
	{
		auto button = std::make_pair(buttonDirection.first, dae::GameController::ButtonState::Pressed);
		auto pMoveCommand = std::make_unique<dae::MoveCommand>(player, speed, buttonDirection.second);
		controller1->AttachCommandToButton(std::move(pMoveCommand), button);
	}	

	scene.Add(player1);

	auto P2 = std::make_shared<dae::GameObject>("p2");
	P2->SetPosition(glm::vec3{ 350,350,0 });

	textureComponent = std::make_shared<dae::TextureComponent>(P2, "char2.png");
	P2->AddComponent<dae::TextureComponent>(textureComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(P2);
	P2->AddComponent<dae::RenderComponent>(renderComponent);

	scene.Add(P2);



}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}