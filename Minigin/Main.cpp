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
	//TODO create different gameobject
	//Background texture component
	auto bgGo = std::make_shared<dae::GameObject>();
	auto bgTexture = std::make_shared<dae::TextureComponent>(bgGo.get());
	bgTexture->SetTexture("background.tga");
	bgGo->AddComponent(bgTexture);

	scene.Add(bgGo);
	
	//Logo texture component
	auto logoGo = std::make_shared<dae::GameObject>();
	auto logoTexture = std::make_shared<dae::TextureComponent>(logoGo.get());
	logoTexture->SetPosition(216.0f, 180.0f);
	logoTexture->SetTexture("logo.tga");
	logoGo->AddComponent(logoTexture);

	scene.Add(logoGo);

	//Text component
	auto textGo = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_shared<dae::TextComponent>(textGo.get());
	text->SetPosition(80, 20);
	text->SetText("Programming 4 Assignment");
	text->SetFont(font);
	textGo->AddComponent(text);

	scene.Add(textGo);

	//FPS component
	auto fpsGo = std::make_shared<dae::GameObject>();

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsText = std::make_shared<dae::TextComponent>(fpsGo.get());
	fpsText->SetText("FPS");
	fpsText->SetFont(fpsFont);
	fpsGo->AddComponent(fpsText);

	auto fps = std::make_shared<dae::FPSComponent>(fpsGo.get());
	fpsGo->AddComponent(fps);


	scene.Add(fpsGo);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}