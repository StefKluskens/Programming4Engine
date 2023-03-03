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
	auto go = std::make_shared<dae::GameObject>();
	auto bgTexture = std::make_shared<dae::TextureComponent>();
	bgTexture->SetTexture("background.tga");
	go->AddComponent(bgTexture);
	
	//Logo texture component
	auto logoTexture = std::make_shared<dae::TextureComponent>();
	logoTexture->SetPosition(216.0f, 180.0f);
	logoTexture->SetTexture("logo.tga");
	go->AddComponent(logoTexture);

	//Text component
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
	text->SetPosition(80, 20);
	go->AddComponent(text);

	//FPS component
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsText = std::make_shared<dae::TextComponent>("FPS", fpsFont);
	auto fps = std::make_shared<dae::FPSComponent>(fpsText);

	go->AddComponent(fps);
	go->AddComponent(fpsText);

	scene.Add(go);

	//go->RemoveComponent<dae::TextureComponent>();
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}