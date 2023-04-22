#include "GameScene.h"

#include <SDL.h>

#include "GameObject.h"
#include "Scene.h"

// managers
#include "SceneManager.h"

// components
#include "Player.h"
#include "Texture.h"
#include "TextureRenderer.h"
#include "Sprite.h"
#include "SpriteRenderer.h"





void dae::GameScene::LoadScene()
{
	// Create scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background

	CreateBackground(scene);

	// player
	CreatePlayer(scene);
	std::cout << "Player created! \n";

	// sprite test
	auto spriteObj{ std::make_shared<GameObject>("SpriteTest") };
	spriteObj->AddComponent<Sprite>("General_Sprites.png",SDL_Rect(75,58,16,16),2.f);
	spriteObj->AddComponent<SpriteRenderer>();
	scene.Add(spriteObj);

	std::cout << "Sprite added to scene \n";

}

void dae::GameScene::CreatePlayer(Scene& scene)
{
	auto pPlayer{ std::make_shared<GameObject>("player") };
	pPlayer->AddComponent<Player>()->InitPlayer();

	scene.Add(pPlayer);
}

// temporary

void dae::GameScene::CreateBackground(Scene& scene)
{
	auto background = std::make_shared<dae::GameObject>("background");
	background->AddComponent<Texture>()->SetTextureByPath("background.tga");
	background->AddComponent<TextureRenderer>();

	scene.Add(background);
}