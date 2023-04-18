#include <SDL.h>
#include <steam_api.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/glm.hpp>

#include <iostream>

#include "Minigin.h"
#include "DemoSceneLoader.h"
#include "AchievementManager.h"

using namespace dae;

void load()
{
	static AchievementsManager achievementsManager;
	DemoSceneLoader demo;
}

int main(int, char*[]) {
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
	}
	dae::Minigin engine("../Data/");
	engine.Run(load);
	SteamAPI_Shutdown();
    return 0;
}