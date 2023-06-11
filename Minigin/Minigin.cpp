#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include <chrono>

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

void PrintHowToPlay()
{
	printf("\nHow to play:\n\n");
	printf("Player 1 keyboard movement: A/D\n");
	printf("Player 1 keyboard jumping: W\n");
	printf("Player 1 keyboard shooting: J\n");
	printf("Player 1 controller movement: Dpad left/right\n");
	printf("Player 1 controller jumping: Dpad up\n");
	printf("Player 1 controller shooting: B-button\n");

	printf("\n");

	printf("Player 2 keyboard movement: left/right arrow\n");
	printf("Player 2 keyboard jumping: up arrow\n");
	printf("Player 2 keyboard shooting: 0\n");
	printf("Player 2 controller movement: Dpad left/right\n");
	printf("Player 2 controller jumping: Dpad up\n");
	printf("Player 2 controller shooting: B-button\n");
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
		768,
		672,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
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
	PrintHowToPlay();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	int frameTimeMs = 6;
	float lag = 0.f; 
	const float fixedTimeStepSec{ 0.02f };

	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

		lastTime = currentTime;
		lag += deltaTime;


		doContinue = input.ProcessInput(deltaTime);

		while (lag >= fixedTimeStepSec)
		{
			sceneManager.FixedUpdate(fixedTimeStepSec);
			lag -= fixedTimeStepSec;
		}

		sceneManager.Update(deltaTime);
		renderer.Render();


		const auto sleepTime = currentTime + std::chrono::milliseconds(frameTimeMs) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}
