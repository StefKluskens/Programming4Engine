#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "LivesComponent.h"
#include "LivesDisplayComponent.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include <glm/glm.hpp>

#include <steam_api.h>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background texture object
	auto bgGo = new dae::GameObject("Background object");
	auto bgTexture = std::make_unique<dae::TextureComponent>(bgGo);
	bgTexture->SetTexture("background.tga");
	bgGo->AddComponent(std::move(bgTexture));
	scene.Add(bgGo);
	
	//Logo texture object
	auto logoGo = new dae::GameObject("Logo object");
	logoGo->SetPosition(216.0f, 180.0f);
	auto logoTexture = std::make_unique<dae::TextureComponent>(logoGo);
	logoTexture->SetTexture("logo.tga");
	logoGo->AddComponent(std::move(logoTexture));
	scene.Add(logoGo);

	//Text object
	auto textGo = new dae::GameObject("Programming text object");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_unique<dae::TextComponent>(textGo, "Programming 4 Assignment", font);
	text->SetPosition(80, 20);
	textGo->AddComponent(std::move(text));
	scene.Add(textGo);

	//FPS object
	auto fpsGo = new dae::GameObject("FPS object");
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsText = std::make_unique<dae::TextComponent>(fpsGo, "FPS", fpsFont);
	fpsGo->AddComponent(std::move(fpsText));
	auto fps = std::make_unique<dae::FPSComponent>(fpsGo);
	fpsGo->AddComponent(std::move(fps));
	fpsGo->SetPosition(0.f, 0.f);
	scene.Add(fpsGo);

	//Bob
	auto bobGo = new dae::GameObject("Bob object");
	bobGo->SetPosition(350.0f, 350.0f);

	auto bobTexture = std::make_unique<dae::TextureComponent>(bobGo);
	bobTexture->SetTexture("Resources/Bob.png");
	bobGo->AddComponent(std::move(bobTexture));

	auto bobLivesComponent = std::make_unique<dae::LivesComponent>(bobGo, 3);
	bobGo->AddComponent(std::move(bobLivesComponent));

	auto bobScoreComponent = std::make_unique<dae::ScoreComponent>(bobGo);
	bobGo->AddComponent(std::move(bobScoreComponent));

	scene.Add(bobGo);

	//Lives display bob
	auto livesDisplayGo = new dae::GameObject("Bob lives display");
	livesDisplayGo->SetPosition(0.f, 60.f);

	auto livesFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto livesText = std::make_unique<dae::TextComponent>(livesDisplayGo, "Lives", livesFont);
	livesDisplayGo->AddComponent(std::move(livesText));

	auto livesDisplayBob = std::make_unique<dae::LivesDisplayComponent>(livesDisplayGo, bobGo->GetComponent<dae::LivesComponent>());
	livesDisplayGo->AddComponent(std::move(livesDisplayBob));

	scene.Add(livesDisplayGo);

	bobGo->GetComponent<dae::LivesComponent>()->AddObserver(livesDisplayGo->GetComponent<dae::LivesDisplayComponent>());

	//Score display
	auto scoreDisplayGo = new dae::GameObject("Bob score display");
	scoreDisplayGo->SetPosition(0.f, 80.f);

	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto scoreText = std::make_unique<dae::TextComponent>(scoreDisplayGo, "Score", scoreFont);
	scoreDisplayGo->AddComponent(std::move(scoreText));

	auto scoreDisplayBob = std::make_unique<dae::ScoreDisplay>(scoreDisplayGo, bobGo->GetComponent<dae::ScoreComponent>());
	scoreDisplayGo->AddComponent(std::move(scoreDisplayBob));

	scene.Add(scoreDisplayGo);

	bobGo->GetComponent<dae::ScoreComponent>()->AddObserver(scoreDisplayGo->GetComponent<dae::ScoreDisplay>());

	//Move commands WASD
	auto moveCommand = std::make_unique<dae::MoveCommand>(bobGo, glm::vec3{0.0f, -1.0f, 0.0f}, 50.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(moveCommand));

	moveCommand = std::make_unique<dae::MoveCommand>(bobGo, glm::vec3{ 0.0f, 1.0f, 0.0f }, 50.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(moveCommand));

	moveCommand = std::make_unique<dae::MoveCommand>(bobGo, glm::vec3{ -1.0f, 0.0f, 0.0f }, 50.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(SDLK_a, std::move(moveCommand));

	moveCommand = std::make_unique<dae::MoveCommand>(bobGo, glm::vec3{ 1.0f, 0.0f, 0.0f }, 50.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(SDLK_d, std::move(moveCommand));

	//Die command
	auto dieCommand = std::make_unique<dae::DieCommand>(bobGo, dae::ButtonState::IsDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_r, std::move(dieCommand));

	//Score command
	auto scoreCommand = std::make_unique<dae::ScoreCommand>(bobGo, dae::ButtonState::IsDown);
	dae::InputManager::GetInstance().AddCommand(SDLK_t, std::move(scoreCommand));

	//Bub
	auto bubGo = new dae::GameObject("Bub object");
	bubGo->SetPosition(300.f, 350.f);
	auto bubTexture = std::make_unique<dae::TextureComponent>(bubGo);
	bubTexture->SetTexture("Resources/Bub.png");
	bubGo->AddComponent(std::move(bubTexture));

	auto bubLivesComponent = std::make_unique<dae::LivesComponent>(bubGo, 3);
	bubGo->AddComponent(std::move(bubLivesComponent));

	auto bubScoreComponent = std::make_unique<dae::ScoreComponent>(bubGo);
	bubGo->AddComponent(std::move(bubScoreComponent));

	scene.Add(bubGo);

	//Lives display bub
	auto livesDisplayGoBub = new dae::GameObject("Bub lives display");
	livesDisplayGoBub->SetPosition(0.f, 140.f);

	auto livesFontBub = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto livesTextBub = std::make_unique<dae::TextComponent>(livesDisplayGoBub, "Lives", livesFontBub);
	livesDisplayGoBub->AddComponent(std::move(livesTextBub));

	auto livesDisplayBub = std::make_unique<dae::LivesDisplayComponent>(livesDisplayGoBub, bubGo->GetComponent<dae::LivesComponent>());
	livesDisplayGoBub->AddComponent(std::move(livesDisplayBub));

	scene.Add(livesDisplayGoBub);

	bubGo->GetComponent<dae::LivesComponent>()->AddObserver(livesDisplayGoBub->GetComponent<dae::LivesDisplayComponent>());

	//Score display
	auto scoreDisplayGoBub = new dae::GameObject("Bob score display");
	scoreDisplayGoBub->SetPosition(0.f, 160.f);

	auto scoreFontBub = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto scoreTextBub = std::make_unique<dae::TextComponent>(scoreDisplayGoBub, "Score", scoreFontBub);
	scoreDisplayGoBub->AddComponent(std::move(scoreTextBub));

	auto scoreDisplayBub = std::make_unique<dae::ScoreDisplay>(scoreDisplayGoBub, bubGo->GetComponent<dae::ScoreComponent>());
	scoreDisplayGoBub->AddComponent(std::move(scoreDisplayBub));

	scene.Add(scoreDisplayGoBub);

	bubGo->GetComponent<dae::ScoreComponent>()->AddObserver(scoreDisplayGoBub->GetComponent<dae::ScoreDisplay>());

	//Add new xbox controller
	int controllerIndex = dae::InputManager::GetInstance().AddXBoxController();

	//Move commands for dpad
	moveCommand = std::make_unique<dae::MoveCommand>(bubGo, glm::vec3{ 0.0f, -1.0f, 0.0f }, 100.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(moveCommand), controllerIndex);

	moveCommand = std::make_unique<dae::MoveCommand>(bubGo, glm::vec3{ 0.0f, 1.0f, 0.0f }, 100.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadDown, std::move(moveCommand), controllerIndex);

	moveCommand = std::make_unique<dae::MoveCommand>(bubGo, glm::vec3{ -1.0f, 0.0f, 0.0f }, 100.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadLeft, std::move(moveCommand), controllerIndex);

	moveCommand = std::make_unique<dae::MoveCommand>(bubGo, glm::vec3{ 1.0f, 0.0f, 0.0f }, 100.f, dae::ButtonState::IsPressed);
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadRight, std::move(moveCommand), controllerIndex);

	//Die command
	dieCommand = std::make_unique<dae::DieCommand>(bubGo, dae::ButtonState::IsDown);
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::ButtonA, std::move(dieCommand), controllerIndex);

	//Score command
	scoreCommand = std::make_unique<dae::ScoreCommand>(bubGo, dae::ButtonState::IsDown);
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::ButtonB, std::move(scoreCommand), controllerIndex);
}

int main(int, char*[]) 
{
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n";
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam.\n";
	}
	
	dae::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();
    return 0;
}