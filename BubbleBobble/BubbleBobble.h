#pragma once
class BubbleBobble
{
	enum class GameMode
	{
		SinglePlayer,
		MultiPlayer,
		Versus
	};

public:
	void Load();

	GameMode GetGameMode() const;
	void SetGameMode(GameMode gameMode);

private:
	GameMode m_CurrentGameMode{};
};

