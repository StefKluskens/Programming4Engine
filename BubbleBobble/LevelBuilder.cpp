#include "LevelBuilder.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TileComponent.h"
#include <sstream>
#include <memory>
#include "InputManager.h"
#include "Commands.h"
#include "BubbleBobble.h"

void Game::LevelBuilder::BuildLevel(dae::Scene* pScene, std::string levelFile, int sceneNr)
{
	m_pFile = dae::ResourceManager::GetInstance().LoadTextFile(levelFile);

	m_SceneNr = sceneNr;

	if (m_pFile->is_open())
	{
		std::string line;
		while (!m_pFile->eof())
		{
			std::getline(*m_pFile.get(), line);
			
			if (line.rfind("BigCol ", 0) == 0)
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

void Game::LevelBuilder::BuildMainMenu(dae::Scene* pScene, int controllerIndex1, int controllerIndex2)
{
	auto& input = dae::InputManager::GetInstance();
	BubbleBobble& bubbleBobble = BubbleBobble::GetInstance();

	//Command object
	dae::GameObject* commandGO = new dae::GameObject("CommandsHolder", pScene);
	pScene->Add(commandGO);

	//Single player
	auto pLoadSceneCommand = std::make_unique<LoadSceneCommand>(pScene, commandGO, 0, dae::Command::ButtonState::IsDown, bubbleBobble, controllerIndex1, controllerIndex2);
	input.AddCommand(pScene->GetName(), SDL_SCANCODE_LEFT, std::move(pLoadSceneCommand));

	pLoadSceneCommand = std::make_unique<LoadSceneCommand>(pScene, commandGO, 0, dae::Command::ButtonState::IsDown, bubbleBobble, controllerIndex1, controllerIndex2);
	input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadLeft, std::move(pLoadSceneCommand), controllerIndex1);

	//Coop
	pLoadSceneCommand = std::make_unique<LoadSceneCommand>(pScene, commandGO, 1, dae::Command::ButtonState::IsDown, bubbleBobble, controllerIndex1, controllerIndex2);
	input.AddCommand(pScene->GetName(), SDL_SCANCODE_RIGHT, std::move(pLoadSceneCommand));

	pLoadSceneCommand = std::make_unique<LoadSceneCommand>(pScene, commandGO, 1, dae::Command::ButtonState::IsDown, bubbleBobble, controllerIndex1, controllerIndex2);
	input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadRight, std::move(pLoadSceneCommand), controllerIndex1);

	//Versus
	pLoadSceneCommand = std::make_unique<LoadSceneCommand>(pScene, commandGO, 2, dae::Command::ButtonState::IsDown, bubbleBobble, controllerIndex1, controllerIndex2);
	input.AddCommand(pScene->GetName(), SDL_SCANCODE_UP, std::move(pLoadSceneCommand));

	pLoadSceneCommand = std::make_unique<LoadSceneCommand>(pScene, commandGO, 2, dae::Command::ButtonState::IsDown, bubbleBobble, controllerIndex1, controllerIndex2);
	input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadUp, std::move(pLoadSceneCommand), controllerIndex1);
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
