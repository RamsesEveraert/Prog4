#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "DemoSceneLoader.h"

#include "Minigin.h"
#include "GameScene.h"

using namespace dae;

void load()
{
	GameScene game;
	game.LoadScene();
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}