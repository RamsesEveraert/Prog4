#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "LevelManager.h"
#include "ServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"

#include "Event.h"


using namespace dae;

void load()
{
#if _DEBUG
	ServiceLocator::RegisterAudioSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SDLSoundSystem>()));
#else
	ServiceLocator::RegisterAudioSystem(std::make_unique<SDLSoundSystem>());
#endif

	LevelManager::GetInstance().LoadStartScreen();
	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}