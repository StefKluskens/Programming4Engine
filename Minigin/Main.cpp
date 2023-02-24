#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include <glm/glm.hpp>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	/*auto go = std::make_shared<dae::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);*/

	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto go = std::make_shared<dae::GameObject>();
	auto text = new dae::TextComponent("Programming 4 Assignment", font);
	text->SetPosition(80, 20);

	go->AddComponent(text);

	auto texture = new dae::TextureComponent();
	texture->SetPosition(216.0f, 180.0f);
	texture->SetTexture("logo.tga");

	go->AddComponent(texture);

	scene.Add(go);

	//go->RemoveComponent<dae::TextureComponent>();
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}