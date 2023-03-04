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
#include <glm/glm.hpp>

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
	//logoTexture->SetPosition(216.0f, 180.0f);
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
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}