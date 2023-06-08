#pragma once
#include "Singleton.h"

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

private:
	GameMode m_CurrentGameMode{};
};

