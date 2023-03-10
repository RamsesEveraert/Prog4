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
#include "Scene.h"

#include "GameObject.h"

#include "TextComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
		

	// background

	auto background = std::make_shared<dae::GameObject>();

	auto textureComponent = std::make_shared<dae::TextureComponent>(background, "background.tga");
	background->AddComponent<dae::TextureComponent>(textureComponent);

	auto transformComponent = std::make_shared<dae::TransformComponent>(background);
	background->AddComponent<dae::TransformComponent>(transformComponent);

	auto renderComponent = std::make_shared<dae::RenderComponent>(background);
	background->AddComponent<dae::RenderComponent>(renderComponent);

	background->GetComponent<dae::TransformComponent>()->SetLocalPosition(glm::vec3{0,0,0});
	
	scene.Add(background);

	// logo

	auto logo = std::make_shared<dae::GameObject>();

	textureComponent = std::make_shared<dae::TextureComponent>(logo, "logo.tga");
	logo->AddComponent<dae::TextureComponent>(textureComponent);

	transformComponent = std::make_shared<dae::TransformComponent>(logo);
	logo->AddComponent<dae::TransformComponent>(transformComponent);
	
	renderComponent = std::make_shared<dae::RenderComponent>(logo);
	logo->AddComponent<dae::RenderComponent>(renderComponent);	

	logo->GetComponent<dae::TransformComponent>()->SetLocalPosition(glm::vec3{216,190,0});

	scene.Add(logo);


	// textobject

	auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	textureComponent = std::make_shared<dae::TextureComponent>(textObject, ""); // empty string used as null
	textObject->AddComponent<dae::TextureComponent>(textureComponent);

	auto textComponent = std::make_shared<dae::TextComponent>(textObject, "Programming 4: ", font);
	textObject->AddComponent<dae::TextComponent>(textComponent);

	transformComponent = std::make_shared<dae::TransformComponent>(textObject);
	textObject->AddComponent<dae::TransformComponent>(transformComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(textObject);
	textObject->AddComponent<dae::RenderComponent>(renderComponent);	

	textObject.get()->GetComponent<dae::TransformComponent>()->SetLocalPosition(glm::vec3{190,250,0});

	scene.Add(textObject);

	// FPSobject

	auto fpsCounter = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	textureComponent = std::make_shared<dae::TextureComponent>(fpsCounter, "");// empty string used as null
	fpsCounter->AddComponent<dae::TextureComponent>(textureComponent);

	transformComponent = std::make_shared<dae::TransformComponent>(fpsCounter);
	fpsCounter->AddComponent<dae::TransformComponent>(transformComponent);

	textComponent = std::make_shared<dae::TextComponent>(fpsCounter, " ", font); 
	fpsCounter->AddComponent<dae::TextComponent>(textComponent);

	
	renderComponent = std::make_shared<dae::RenderComponent>(fpsCounter);
	fpsCounter->AddComponent<dae::RenderComponent>(renderComponent);

	auto fpsComponent = std::make_shared<dae::FPSComponent>(fpsCounter);
	fpsCounter->AddComponent<dae::FPSComponent>(fpsComponent);	

	fpsCounter->GetComponent<dae::TransformComponent>()->SetLocalPosition(glm::vec3{20,20,0});

	scene.Add(fpsCounter);

	// test centerpoint

	auto centerPoint = std::make_shared<dae::GameObject>();


	textureComponent = std::make_shared<dae::TextureComponent>(centerPoint, "char1.png");
	centerPoint->AddComponent<dae::TextureComponent>(textureComponent);

	transformComponent = std::make_shared<dae::TransformComponent>(centerPoint);
	centerPoint->AddComponent<dae::TransformComponent>(transformComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(centerPoint);
	centerPoint->AddComponent<dae::RenderComponent>(renderComponent);

	centerPoint.get()->GetComponent<dae::TransformComponent>()->SetLocalPosition(glm::vec3{ 300,300,0 });
	scene.Add(centerPoint);

	// Rotating object 1

	auto parentObject = std::make_shared<dae::GameObject>();


	textureComponent = std::make_shared<dae::TextureComponent>(parentObject, "char1.png");
	parentObject->AddComponent<dae::TextureComponent>(textureComponent);

	transformComponent = std::make_shared<dae::TransformComponent>(parentObject);
	parentObject->AddComponent<dae::TransformComponent>(transformComponent);

	auto rotatorComponent = std::make_shared<dae::RotatorComponent>(parentObject);
	parentObject->AddComponent<dae::RotatorComponent>(rotatorComponent);

	renderComponent = std::make_shared<dae::RenderComponent>(parentObject);
	parentObject->AddComponent<dae::RenderComponent>(renderComponent);

	parentObject.get()->GetComponent<dae::RotatorComponent>()->SetCenterPoint(glm::vec3{ 300,300, 0 });
	parentObject.get()->GetComponent<dae::RotatorComponent>()->SetRadius(100.f);
	parentObject.get()->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(1.f);

	scene.Add(parentObject);

	// Rotating object 2

	auto childObject = std::make_shared<dae::GameObject>();


	textureComponent = std::make_shared<dae::TextureComponent>(childObject, "char2.png");
	childObject->AddComponent<dae::TextureComponent>(textureComponent);

	transformComponent = std::make_shared<dae::TransformComponent>(childObject);
	childObject->AddComponent<dae::TransformComponent>(transformComponent);

	rotatorComponent = std::make_shared<dae::RotatorComponent>(childObject);
	childObject->AddComponent<dae::RotatorComponent>(rotatorComponent);

	childObject->SetParent(parentObject, true);

	childObject.get()->GetComponent<dae::RotatorComponent>()->SetCenterPoint(parentObject->GetComponent<dae::TransformComponent>()->GetWorldPosition());
	childObject.get()->GetComponent<dae::RotatorComponent>()->SetRadius(25.f);
	childObject.get()->GetComponent<dae::RotatorComponent>()->SetRotationSpeed(-4.f);

	renderComponent = std::make_shared<dae::RenderComponent>(childObject);
	childObject->AddComponent<dae::RenderComponent>(renderComponent);

	scene.Add(childObject);

	// delete tests works
	/*logo->MarkForDelete();
	background->MarkForDelete();*/


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}