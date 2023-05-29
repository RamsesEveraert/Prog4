#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "LevelManager.h"

using namespace dae;

void load()
{
	LevelManager::GetInstance().LoadStartScreen();
	/*auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	LevelManager::GetInstance().LoadLevel(scene, GameMode::SINGLEPLAYER, 1);*/
	

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}