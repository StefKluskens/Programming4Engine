#include "LevelBuilder.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TileComponent.h"
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
			else if (line.rfind("SmallTile ", 0) == 0)
			{
				BuildTile(pScene, line, true, m_NrTile);
				++m_NrTile;
			}
			else if (line.rfind("BigTile ", 0) == 0)
			{
				BuildTile(pScene, line, false, m_NrTile);
				++m_NrTile;
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

void Game::LevelBuilder::BuildTile(dae::Scene* pScene, std::string line, bool isSmallTile, int tileNr)
{
	//Tile line will be formatted as:
	//Tile xPos yPos
	std::stringstream ss(line);

	std::string tile;
	float xPos, yPos;

	ss >> tile >> xPos >> yPos;

	std::string name = "Tile " + tileNr;

	auto tileGo = new dae::GameObject(name, pScene);

	tileGo->SetPosition(xPos, yPos);

	auto pTile = std::make_unique<TileComponent>(tileGo, isSmallTile);

	pScene->Add(tileGo);
}
