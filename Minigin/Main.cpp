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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
		

	// objects

	auto background = std::make_shared<dae::GameObject>();
	background->SetTexture("background.tga");
	scene.Add(background);

	auto logo = std::make_shared<dae::GameObject>();
	auto transformComponent = std::make_shared<dae::TransformComponent>(logo);
	logo->SetTexture("logo.tga");
	logo->addComponent(transformComponent);
	logo->getComponent<dae::TransformComponent>()->SetPosition(glm::vec3{216,180,0}); // werkt
	scene.Add(logo);

	/*auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

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