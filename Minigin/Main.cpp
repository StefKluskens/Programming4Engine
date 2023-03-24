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
#include "Rotator.h"
#include <glm/glm.hpp>
#include "InputManager.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background GO
	auto bgGo = std::make_shared<dae::GameObject>();
	auto bgTexture = std::make_shared<dae::TextureComponent>(bgGo.get());
	bgTexture->SetTexture("background.tga");
	bgGo->AddComponent(bgTexture);
	bgGo->SetPosition(0.0f, 0.0f);
	scene.Add(bgGo);
	
	//Logo GO
	auto logoGo = std::make_shared<dae::GameObject>();
	auto logoTexture = std::make_shared<dae::TextureComponent>(logoGo.get());
	logoTexture->SetTexture("logo.tga");
	logoGo->AddComponent(logoTexture);
	logoGo->SetPosition(216.0f, 180.0f);
	scene.Add(logoGo);

	//Text GO
	auto textGo = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_shared<dae::TextComponent>(textGo.get());
	text->SetText("Programming 4 Assignment");
	text->SetFont(font);
	textGo->AddComponent(text);
	textGo->SetPosition(80.0f, 20.0f);
	scene.Add(textGo);

	//FPS GO
	auto fpsGo = std::make_shared<dae::GameObject>();

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsText = std::make_shared<dae::TextComponent>(fpsGo.get());
	fpsText->SetText("FPS");
	fpsText->SetFont(fpsFont);
	fpsGo->AddComponent(fpsText);

	auto fps = std::make_shared<dae::FPSComponent>(fpsGo.get());
	fpsGo->AddComponent(fps);

	fpsGo->SetPosition(0.0f, 0.0f);

	scene.Add(fpsGo);

	//Bob
	auto bobGo = std::make_shared<dae::GameObject>();
	bobGo->SetPosition(300.0f, 300.0f);

	auto bobTexture = std::make_shared<dae::TextureComponent>(bobGo.get());
	bobTexture->SetTexture("Resources/Bob.png");
	bobGo->AddComponent(bobTexture);
	scene.Add(bobGo);

	//Move commands WASD
	auto commandUp = std::make_unique<MoveUp>(bobGo.get());
	dae::InputManager::GetInstance().AddCommand(SDLK_w, std::move(commandUp));

	auto commandDown = std::make_unique<MoveDown>(bobGo.get());
	dae::InputManager::GetInstance().AddCommand(SDLK_s, std::move(commandDown));

	auto commandLeft = std::make_unique<MoveLeft>(bobGo.get());
	dae::InputManager::GetInstance().AddCommand(SDLK_a, std::move(commandLeft));

	auto commandRight = std::make_unique<MoveRight>(bobGo.get());
	dae::InputManager::GetInstance().AddCommand(SDLK_d, std::move(commandRight));

	//Bub
	auto bubGo = std::make_shared<dae::GameObject>();
	bubGo->SetLocalPosition(350.0f, 350.0f);

	auto bubTexture = std::make_shared<dae::TextureComponent>(bubGo.get());
	bubTexture->SetTexture("Resources/Bub.png");
	bubGo->AddComponent(bubTexture);
	scene.Add(bubGo);

	//Add new controller
	int controllerIndex = dae::InputManager::GetInstance().AddXBoxController();

	//Move commands for dpad
	commandUp = std::make_unique<MoveUp>(bubGo.get());
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(commandUp), controllerIndex);

	commandDown = std::make_unique<MoveDown>(bubGo.get());
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadDown, std::move(commandDown), controllerIndex);

	commandLeft = std::make_unique<MoveLeft>(bubGo.get());
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadLeft, std::move(commandLeft), controllerIndex);

	commandRight = std::make_unique<MoveRight>(bubGo.get());
	dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadRight, std::move(commandRight), controllerIndex);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}