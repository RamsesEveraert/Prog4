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
#include "TextObject.h"
#include "Scene.h"

#include "TextComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
		

	// background

	auto background = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(background, "background.tga");
	auto transformComponent = std::make_shared<dae::TransformComponent>(background);
	auto renderComponent = std::make_shared<dae::RenderComponent>(background);

	background->addComponent<dae::TransformComponent>(transformComponent);
	background->addComponent<dae::TextureComponent>(texture);
	background->addComponent<dae::RenderComponent>(renderComponent);
	background->getComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 0,0,0 });
	
	scene.Add(background);

	// logo

	auto logo = std::make_shared<dae::GameObject>();
	transformComponent = std::make_shared<dae::TransformComponent>(logo);
	texture = std::make_shared<dae::TextureComponent>(logo, "logo.tga");
	renderComponent = std::make_shared<dae::RenderComponent>(logo);

	logo->addComponent<dae::TransformComponent>(transformComponent);
	logo->addComponent<dae::TextureComponent>(texture);
	logo->addComponent<dae::RenderComponent>(renderComponent);
	logo->getComponent<dae::TransformComponent>()->SetPosition(glm::vec3{ 216,18,0 });

	scene.Add(logo);

	// textobject


	auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	


	/*
	

	auto textComponent = std::make_shared<dae::TextComponent>("Programming 4: ", font);

	textObject.get()->AddComponent(textComponent);
	textObject.get()->AddComponent(transformComponent);
	textObject.get()->GetComponent<dae::TransformComponent>().lock()->SetPosition(80, 20);
	scene.Add(textObject);*/


	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/



}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}