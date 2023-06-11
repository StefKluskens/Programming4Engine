#include "BubbleBobble.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelBuilder.h"
#include "PlayerBuilder.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ScoreComponent.h"

void BubbleBobble::Load()
{
	int controllerIndexP1 = dae::InputManager::GetInstance().AddXBoxController();
	int controllerIndexP2 = dae::InputManager::GetInstance().AddXBoxController();
	auto& mainMenu = dae::SceneManager::GetInstance().CreateScene("MainMenu");

	m_LevelBuilder = Game::LevelBuilder();
	m_PlayerBuilder = Game::PlayerBuilder();

	m_LevelBuilder.BuildMainMenu(&mainMenu, controllerIndexP1, controllerIndexP2);
	printf("got here\n");

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
	m_LevelBuilder.BuildLevel(&level0, "Resources/Levels/Level0.txt", 0);
	m_NrOfEnemiesLevel0 = static_cast<int>(level0.GetRoot()->GetChildrenByTag("Enemy").size());

	auto& level1 = dae::SceneManager::GetInstance().CreateScene("Level1");
	m_LevelBuilder.BuildLevel(&level1, "Resources/Levels/Level1.txt", 1);
	m_NrOfEnemiesLevel1 = static_cast<int>(level0.GetRoot()->GetChildrenByTag("Enemy").size());

	auto& level2 = dae::SceneManager::GetInstance().CreateScene("Level2");
	m_LevelBuilder.BuildLevel(&level2, "Resources/Levels/Level2.txt", 2);
	m_NrOfEnemiesLevel2 = static_cast<int>(level0.GetRoot()->GetChildrenByTag("Enemy").size());

	auto scenes = dae::SceneManager::GetInstance().GetScenes();
	for (auto scene : scenes)
	{
		if (scene->GetName() == "MainMenu")
		{
			continue;
		}
		m_PlayerBuilder.BuildPlayer("Resources/Levels/PlayerData.txt", scene.get(), controllerIndex1, controllerIndex2, static_cast<int>(m_CurrentGameMode));
		m_LevelBuilder.CreateObservers(scene.get());
	}
}

void BubbleBobble::LoadNextScene()
{
	const std::string& sceneName = dae::SceneManager::GetInstance().GetActiveScene()->GetName();

	if (sceneName == "Level0")
	{
		auto pScene = dae::SceneManager::GetInstance().GetActiveScene();
		auto playersOld = pScene->GetRoot()->GetChildrenByTag("Player");

		dae::SceneManager::GetInstance().SetActiveScene("Level1");

		pScene = dae::SceneManager::GetInstance().GetActiveScene();
		auto playersNew = pScene->GetRoot()->GetChildrenByTag("Player");

		std::vector<int> scores{};

		for (auto player : playersOld)
		{
			scores.push_back(player->GetComponent<Game::ScoreComponent>()->GetScore());
		}

		for (size_t i = 0; i < playersNew.size(); ++i)
		{
			playersNew[i]->GetComponent<Game::ScoreComponent>()->AddScore(scores[i]);
		}
	}
	else if (sceneName == "Level1")
	{
		auto pScene = dae::SceneManager::GetInstance().GetActiveScene();
		auto playersOld = pScene->GetRoot()->GetChildrenByTag("Player");

		dae::SceneManager::GetInstance().SetActiveScene("Level2");

		pScene = dae::SceneManager::GetInstance().GetActiveScene();
		auto playersNew = pScene->GetRoot()->GetChildrenByTag("Player");

		std::vector<int> scores{};

		for (auto player : playersOld)
		{
			scores.push_back(player->GetComponent<Game::ScoreComponent>()->GetScore());
		}

		for (size_t i = 0; i < playersNew.size(); ++i)
		{
			playersNew[i]->GetComponent<Game::ScoreComponent>()->AddScore(scores[i]);
		}
	}
	/*else if (sceneName == "Level2")
	{
		dae::SceneManager::GetInstance().SetActiveScene("Level0");
	}*/

	m_NrOfEnemiesKilled = 0;
}

void BubbleBobble::IncreaseKillNr()
{
	++m_NrOfEnemiesKilled;
}

bool BubbleBobble::ShouldLoadNewLevel() const
{
	const std::string& sceneName = dae::SceneManager::GetInstance().GetActiveScene()->GetName();

	if (sceneName == "Level0")
	{
		return m_NrOfEnemiesKilled == m_NrOfEnemiesLevel0;
	}
	else if (sceneName == "Level1")
	{
		return m_NrOfEnemiesKilled == m_NrOfEnemiesLevel1;
	}
	else if (sceneName == "Level2")
	{
		return m_NrOfEnemiesKilled == m_NrOfEnemiesLevel2;
	}

	return false;
}
