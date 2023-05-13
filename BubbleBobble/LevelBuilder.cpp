#include "LevelBuilder.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include <sstream>
#include <memory>

void Game::LevelBuilder::BuildLevel(dae::Scene* pScene, std::string levelFile)
{
	m_pFile = dae::ResourceManager::GetInstance().LoadTextFile(levelFile);

	if (m_pFile->is_open())
	{
		std::string line;
		while (!m_pFile->eof())
		{
			std::getline(*m_pFile.get(), line);
			
			if (line.rfind("Player ", 0) == 0)
			{
				BuildPlayer(pScene, line);
			}
		}
	}
}

void Game::LevelBuilder::BuildPlayer(dae::Scene* pScene, std::string line)
{
	//Player line will be formatted as:
	//Player xPos yPos isPLayer1 hasCollider hasRB
	std::stringstream ss(line);

	std::string player;
	float xPos, yPos;
	bool isPlayer1, hasCollider, hasRB;

	ss >> player >> xPos >> yPos >> std::boolalpha >> isPlayer1 >> hasCollider >> hasRB;
	
	std::string name = "Player 1";

	if (!isPlayer1)
	{
		name = "Player 2";
	}
	auto playerGo = new dae::GameObject(name, pScene);

	playerGo->SetPosition(xPos, yPos);

	auto playerComp = std::make_unique<PlayerComponent>(playerGo, isPlayer1, hasCollider, hasRB);
	playerGo->AddComponent(std::move(playerComp));

	pScene->Add(playerGo);
}
