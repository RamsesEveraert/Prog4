#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "Timer.h"

#include <chrono>
#include <thread>

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		336,
		432,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{

	load();

	auto& timeManager = TimeManager::GetInstance();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	const float targetFPS = 60.f;
	const float fixedTimeStep = 1.0f / targetFPS; // target frame time is 1/60th of a second
	float accumulatedTime = 0.0f;

	bool doContinue = true;

	while (doContinue)
	{
		timeManager.Update();

		const float dt = timeManager.GetDeltaTimeSec();
		accumulatedTime += dt;

		doContinue = input.ProcessInput();

		// Perform fixed timestep updates
		while (accumulatedTime >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(/*fixedTimeStep*/);
			accumulatedTime -= fixedTimeStep;
		}
				
		sceneManager.Update();

		renderer.Render();

		// Sleep to ensure a fixed frame rate
		const auto endTime = std::chrono::steady_clock::now() + std::chrono::microseconds(static_cast<int>(fixedTimeStep * 1000000));
		std::this_thread::sleep_until(endTime);

		//if (accumulatedTime < fixedTimeStep)
		//{
		//	// sleep to avoid using GPU resources unnecessarily
		//	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((fixedTimeStep - accumulatedTime) * 1000)));
		//}
		
	}



}

