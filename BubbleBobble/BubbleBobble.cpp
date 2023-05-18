#include "BubbleBobble.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelBuilder.h"
#include "InputManager.h"

void BubbleBobble::Load()
{
	int controllerIndexP1 = dae::InputManager::GetInstance().AddXBoxController();
	int controllerIndexP2 = dae::InputManager::GetInstance().AddXBoxController();

	auto& level0 = dae::SceneManager::GetInstance().CreateScene("Level0");
	Game::LevelBuilder::GetInstance().BuildLevel(&level0, "Resources/Levels/Level0.txt", 0, controllerIndexP1, controllerIndexP2);

	auto& level1 = dae::SceneManager::GetInstance().CreateScene("Level1");
	//controllerIndex = dae::InputManager::GetInstance().AddXBoxController();
	Game::LevelBuilder::GetInstance().BuildLevel(&level1, "Resources/Levels/Level1.txt", 1, controllerIndexP1, controllerIndexP2);

	auto& level2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	Game::LevelBuilder::GetInstance().BuildLevel(&level2, "Resources/Levels/Level2.txt", 2, controllerIndexP1, controllerIndexP2);

	dae::SceneManager::GetInstance().SetActiveScene(level0.GetName());
}

BubbleBobble::GameMode BubbleBobble::GetGameMode() const
{
	return m_CurrentGameMode;
}

void BubbleBobble::SetGameMode(GameMode gameMode)
{
	m_CurrentGameMode = gameMode;
}
