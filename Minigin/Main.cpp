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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
		

	// background

	auto background = std::make_shared<dae::GameObject>();

	auto textureComponent = std::make_shared<dae::TextureComponent>(background, "background.tga");
	auto transformComponent = std::make_shared<dae::TransformComponent>(background);
	auto renderComponent = std::make_shared<dae::RenderComponent>(background);	

	background->AddComponent<dae::TextureComponent>(textureComponent);
	background->AddComponent<dae::TransformComponent>(transformComponent);	
	background->AddComponent<dae::RenderComponent>(renderComponent);

	background->GetComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 0,0,0 });
	
	scene.Add(background);

	// logo

	auto logo = std::make_shared<dae::GameObject>();
	transformComponent = std::make_shared<dae::TransformComponent>(logo);
	textureComponent = std::make_shared<dae::TextureComponent>(logo, "logo.tga");
	renderComponent = std::make_shared<dae::RenderComponent>(logo);

	logo->AddComponent<dae::TextureComponent>(textureComponent);
	logo->AddComponent<dae::TransformComponent>(transformComponent);
	logo->AddComponent<dae::RenderComponent>(renderComponent);

	logo->GetComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 216,190,0 });

	scene.Add(logo);

	// textobject

	auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	textureComponent = std::make_shared<dae::TextureComponent>(textObject, ""); // empty string used as null
	auto textComponent = std::make_shared<dae::TextComponent>(textObject, "Programming 4: ", font);
	transformComponent = std::make_shared<dae::TransformComponent>(textObject);
	renderComponent = std::make_shared<dae::RenderComponent>(textObject);

	textObject->AddComponent<dae::TextureComponent>(textureComponent);
	textObject->AddComponent<dae::TextComponent>(textComponent);
	textObject->AddComponent<dae::TransformComponent>(transformComponent);
	textObject->AddComponent<dae::RenderComponent>(renderComponent);

	textObject.get()->GetComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 190,250,0 });

	scene.Add(textObject);

	// FPSobject

	auto fpsCounter = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	textureComponent = std::make_shared<dae::TextureComponent>(fpsCounter, ""); // empty string used as null
	auto fpsComponent = std::make_shared<dae::FPSComponent>(fpsCounter);
	textComponent = std::make_shared<dae::TextComponent>(fpsCounter, "test ", font);
	transformComponent = std::make_shared<dae::TransformComponent>(fpsCounter);
	renderComponent = std::make_shared<dae::RenderComponent>(fpsCounter);

	fpsCounter->AddComponent<dae::TextureComponent>(textureComponent);
	fpsCounter->AddComponent<dae::FPSComponent>(fpsComponent);
	fpsCounter->AddComponent<dae::TextComponent>(textComponent);
	fpsCounter->AddComponent<dae::TransformComponent>(transformComponent);
	fpsCounter->AddComponent<dae::RenderComponent>(renderComponent);

	fpsCounter.get()->GetComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 20,20,0 });

	scene.Add(fpsCounter);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}