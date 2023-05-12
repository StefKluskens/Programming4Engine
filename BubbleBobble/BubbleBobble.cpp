#include "BubbleBobble.h"

#include "SceneManager.h"
#include "ResourceManager.h"
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
#include "ColliderComponent.h"
//#include "Commands.h"
#include "RigidBody.h"
#include "PlayerComponent.h"
#include "LevelBuilder.h"
#include <glm/glm.hpp>

void BubbleBobble::Load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	dae::SceneManager::GetInstance().SetActiveScene(scene.GetName());

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
	auto fps = std::make_unique<Game::FPSComponent>(fpsGo);
	fpsGo->AddComponent(std::move(fps));
	fpsGo->SetPosition(0.f, 0.f);
	scene.Add(fpsGo);

	Game::LevelBuilder::GetInstance().BuildLevel(&scene, "Resources/Levels/Level1.txt");

	auto floorGo = new dae::GameObject("Floor1");
	floorGo->SetPosition(300.0f, 400.0f);

	auto floorPos = floorGo->GetTransform()->GetWorldPosition();
	SDL_Rect floorRect;
	floorRect.x = static_cast<int>(floorPos.x);
	floorRect.y = static_cast<int>(floorPos.y);
	floorRect.h = 10;
	floorRect.w = 200;
	auto floorCollider = std::make_unique<dae::ColliderComponent>(floorGo, floorRect);
	floorCollider->SetMoveable(false);
	floorCollider->SetNeedsCollision(false);
	floorGo->AddComponent(std::move(floorCollider));
	scene.Add(floorGo);
}

BubbleBobble::GameMode BubbleBobble::GetGameMode() const
{
	return m_CurrentGameMode;
}

void BubbleBobble::SetGameMode(GameMode gameMode)
{
	m_CurrentGameMode = gameMode;
}
