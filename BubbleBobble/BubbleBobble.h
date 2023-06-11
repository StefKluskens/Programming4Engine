#pragma once
#include "Singleton.h"
#include <vector>
#include "LevelBuilder.h"
#include "PlayerBuilder.h"

namespace dae
{
	class GameObject;
}

class BubbleBobble : public dae::Singleton<BubbleBobble>
{
public:
	enum class GameMode
	{
		SinglePlayer,
		MultiPlayer,
		Versus
	};

	void Load();

	GameMode GetGameMode() const;
	void SetGameMode(GameMode gameMode);

	void MainMenuExit(int controllerIndex1, int controllerIndex2);

	void LoadNextScene();

	void IncreaseKillNr();
	int GetNrKilled() const { return m_NrOfEnemiesKilled; }
	bool ShouldLoadNewLevel() const;

private:
	GameMode m_CurrentGameMode{};

	std::vector<dae::GameObject*> m_pObjectsToMove{};

	int m_NrOfEnemiesLevel0{};
	int m_NrOfEnemiesLevel1{};
	int m_NrOfEnemiesLevel2{};
	int m_NrOfEnemiesKilled{};

	Game::LevelBuilder m_LevelBuilder;
	Game::PlayerBuilder m_PlayerBuilder;
};

