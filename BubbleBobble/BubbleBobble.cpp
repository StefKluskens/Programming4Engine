#include "BubbleBobble.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelBuilder.h"
#include "PlayerBuilder.h"
#include "InputManager.h"

void BubbleBobble::Load()
{
	int controllerIndexP1 = dae::InputManager::GetInstance().AddXBoxController();
	int controllerIndexP2 = dae::InputManager::GetInstance().AddXBoxController();

	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	Game::LevelBuilder::GetInstance().BuildMainMenu(&mainMenu, controllerIndexP1, controllerIndexP2);

	dae::SceneManager::GetInstance().SetActiveScene(mainMenu.GetName());
}

BubbleBobble::GameMode BubbleBobble::GetGameMode() const
{
	return m_CurrentGameMode;
}

void BubbleBobble::SetGameMode(GameMode gameMode)
{
	m_CurrentGameMode = gameMode;
}

void BubbleBobble::MainMenuExit(int controllerIndex1, int controllerIndex2)
{
	auto& level0 = dae::SceneManager::GetInstance().CreateScene("Level0");
	Game::LevelBuilder::GetInstance().BuildLevel(&level0, "Resources/Levels/Level0.txt", 0);

	auto& level1 = dae::SceneManager::GetInstance().CreateScene("Level1");
	Game::LevelBuilder::GetInstance().BuildLevel(&level1, "Resources/Levels/Level1.txt", 1);

	auto& level2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	Game::LevelBuilder::GetInstance().BuildLevel(&level2, "Resources/Levels/Level2.txt", 2);

	auto scenes = dae::SceneManager::GetInstance().GetScenes();
	for (auto scene : scenes)
	{
		if (scene->GetName() == "MainMenu")
		{
			continue;
		}
		Game::PlayerBuilder::GetInstance().BuildPlayer("Resources/Levels/PlayerData.txt", scene.get(), controllerIndex1, controllerIndex2, static_cast<int>(m_CurrentGameMode));
		Game::LevelBuilder::GetInstance().CreateObservers(scene.get());
	}
}
