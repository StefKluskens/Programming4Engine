#include "LevelBuilder.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TileComponent.h"
#include <sstream>
#include <memory>

void Game::LevelBuilder::BuildLevel(dae::Scene* pScene, std::string levelFile, int sceneNr, int controllerIndex1, int controllerIndex2)
{
	m_pFile = dae::ResourceManager::GetInstance().LoadTextFile(levelFile);

	m_SceneNr = sceneNr;

	if (m_pFile->is_open())
	{
		std::string line;
		while (!m_pFile->eof())
		{
			std::getline(*m_pFile.get(), line);
			
			if (line.rfind("Player ", 0) == 0)
			{
				BuildPlayer(pScene, line, controllerIndex1, controllerIndex2);
			}
			else if (line.rfind("SmallTile ", 0) == 0)
			{
				BuildTile(pScene, line, true);
				++m_NrTile;
			}
			else if (line.rfind("BigTile ", 0) == 0)
			{
				BuildTile(pScene, line, false);
				++m_NrTile;
			}
			else if (line.rfind("BigCol ", 0) == 0)
			{
				BuildBigTileColumn(pScene, line);
			}
			else if (line.rfind("BigRow ", 0) == 0)
			{
				BuildBigTileRow(pScene, line);
			}
			else if (line.rfind("SmallCol ", 0) == 0)
			{
				BuildSmallTileColumn(pScene, line);
			}
			else if (line.rfind("SmallRow ", 0) == 0)
			{
				BuildSmallTileRow(pScene, line);
			}
		}
	}
}

void Game::LevelBuilder::BuildPlayer(dae::Scene* pScene, std::string line, int controllerIndex1, int controllerIndex2)
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

	auto playerComp = std::make_unique<PlayerComponent>(pScene, playerGo, isPlayer1, hasCollider, hasRB, controllerIndex1, controllerIndex2);
	playerGo->AddComponent(std::move(playerComp));

	pScene->Add(playerGo);
}

void Game::LevelBuilder::BuildTile(dae::Scene* pScene, std::string line, bool isSmallTile)
{
	//Tile line will be formatted as:
	//Tile xPos yPos
	std::stringstream ss(line);

	std::string tile;
	float xPos, yPos;

	ss >> tile >> xPos >> yPos;

	std::string name = "Tile";

	auto tileGo = new dae::GameObject(name, pScene);

	tileGo->SetPosition(xPos, yPos);

	auto pTile = std::make_unique<TileComponent>(tileGo, isSmallTile, m_SceneNr);

	pScene->Add(tileGo);
}

void Game::LevelBuilder::BuildBigTileColumn(dae::Scene* pScene, std::string line)
{
	//BigCol xPosTop yPosTop nrOfTiles
	std::stringstream ss(line);

	std::string tile;
	float xPos, yPos;
	int nrOfTiles{};

	ss >> tile >> xPos >> yPos >> nrOfTiles;

	for (int i{}; i < nrOfTiles; ++i)
	{
		std::string name = "Tile";

		auto tileGo = new dae::GameObject(name, pScene);

		tileGo->SetPosition(xPos, yPos + (48 * i));

		auto pTile = std::make_unique<TileComponent>(tileGo, false, m_SceneNr);

		if (i == 0)
		{
			pTile->SetColliderColumn(nrOfTiles);
		}

		pScene->Add(tileGo);
	}
}

void Game::LevelBuilder::BuildBigTileRow(dae::Scene* pScene, std::string line)
{
	//BigRow xPosTop yPosTop nrOfTiles
	std::stringstream ss(line);

	std::string tile;
	float xPos, yPos;
	int nrOfTiles{};

	ss >> tile >> xPos >> yPos >> nrOfTiles;

	for (int i{}; i < nrOfTiles; ++i)
	{
		std::string name = "Tile";

		auto tileGo = new dae::GameObject(name, pScene);

		tileGo->SetPosition(xPos + (48 * i), yPos);

		auto pTile = std::make_unique<TileComponent>(tileGo, false, m_SceneNr);

		if (i == 0)
		{
			pTile->SetColliderRow(nrOfTiles);
		}

		pScene->Add(tileGo);
	}
}

void Game::LevelBuilder::BuildSmallTileColumn(dae::Scene* pScene, std::string line)
{
	//SmallCol xPosTop yPosTop nrOfTiles
	std::stringstream ss(line);

	std::string tile;
	float xPos, yPos;
	int nrOfTiles{};

	ss >> tile >> xPos >> yPos >> nrOfTiles;

	for (int i{}; i < nrOfTiles; ++i)
	{
		std::string name = "Tile";

		auto tileGo = new dae::GameObject(name, pScene);

		tileGo->SetPosition(xPos, yPos + (24 * i));

		auto pTile = std::make_unique<TileComponent>(tileGo, true, m_SceneNr);

		if (i == 0)
		{
			pTile->SetColliderColumn(nrOfTiles);
		}

		pScene->Add(tileGo);
	}
}

void Game::LevelBuilder::BuildSmallTileRow(dae::Scene* pScene, std::string line)
{
	//SmallRow xPosTop yPosTop nrOfTiles
	std::stringstream ss(line);

	std::string tile;
	float xPos, yPos;
	int nrOfTiles{};

	ss >> tile >> xPos >> yPos >> nrOfTiles;

	for (int i{}; i < nrOfTiles; ++i)
	{
		std::string name = "Tile";

		auto tileGo = new dae::GameObject(name, pScene);

		tileGo->SetPosition(xPos + (24 * i), yPos);

		auto pTile = std::make_unique<TileComponent>(tileGo, true, m_SceneNr);

		if (i == 0)
		{
			pTile->SetColliderRow(nrOfTiles);
		}

		pScene->Add(tileGo);
	}
}
