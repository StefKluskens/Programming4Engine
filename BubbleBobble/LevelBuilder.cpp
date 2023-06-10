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
#include "AnimatorComponent.h"
#include "Animation.h"
#include "TextComponent.h"
#include "ZenChanComponent.h"
#include "MaitaComponent.h"
#include "LivesDisplayComponent.h"
#include "LivesComponent.h"

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
			else if (line.rfind("ZenChan ", 0) == 0)
			{
				BuildZenChan(pScene, line);
			}
			else if (line.rfind("Maita ", 0) == 0)
			{
				BuildMaita(pScene, line);
			}
		}
	}
}

void Game::LevelBuilder::BuildMainMenu(dae::Scene* pScene, int controllerIndex1, int controllerIndex2)
{
	auto logoObject = new dae::GameObject("Logo", pScene);
	auto logoTexture = std::make_unique<dae::TextureComponent>(logoObject);
	logoTexture->SetTexture("Resources/Menu/Logo.png");
	logoObject->AddComponent(std::move(logoTexture));	
	logoObject->SetPosition(117.0f, 20.0f);

	pScene->Add(logoObject);

	auto singlePLayerText = new dae::GameObject("Game Mode Text", pScene);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/Pixel_NES.otf", 22);
	auto text = std::make_unique<dae::TextComponent>(singlePLayerText, "<- FOR SINGLE PLAYER", font);
	
	text->SetPosition(200, 500);
	singlePLayerText->AddComponent(std::move(text));
	pScene->Add(singlePLayerText);

	auto coopText = new dae::GameObject("Game Mode Text", pScene);
	text = std::make_unique<dae::TextComponent>(coopText, "-> FOR COOP", font);
	text->SetPosition(200, 530);
	coopText->AddComponent(std::move(text));
	pScene->Add(coopText);

	auto versusText = new dae::GameObject("Game Mode Text", pScene);
	text = std::make_unique<dae::TextComponent>(versusText, "^ FOR VERSUS", font);
	text->SetPosition(200, 560);
	versusText->AddComponent(std::move(text));
	pScene->Add(versusText);

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
	bool top{};

	ss >> tile >> xPos >> yPos >> nrOfTiles >> std::boolalpha >> top;

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

		if (top)
		{
			tileGo->SetTag("Roof");
		}

		pScene->Add(tileGo);
	}
}

void Game::LevelBuilder::BuildZenChan(dae::Scene* pScene, std::string line)
{
	std::stringstream ss(line);

	std::string zenChan;
	float xPos, yPos;

	ss >> zenChan >> xPos >> yPos;

	auto zenChanObject = new dae::GameObject("ZenChan", pScene);
	zenChanObject->SetTag("Enemy");
	auto zenChangComp = std::make_unique<ZenChanComponent>(zenChanObject);
	zenChanObject->AddComponent(std::move(zenChangComp));

	zenChanObject->SetPosition(xPos, yPos);

	pScene->Add(zenChanObject);
}

void Game::LevelBuilder::BuildMaita(dae::Scene* pScene, std::string line)
{
	std::stringstream ss(line);

	std::string maita;
	float xPos, yPos;

	ss >> maita >> xPos >> yPos;

	auto MaitaChanObject = new dae::GameObject("Maita", pScene);
	MaitaChanObject->SetTag("Enemy");
	auto MaitaComp = std::make_unique<MaitaComponent>(MaitaChanObject);
	MaitaChanObject->AddComponent(std::move(MaitaComp));

	MaitaChanObject->SetPosition(xPos, yPos);

	pScene->Add(MaitaChanObject);
}

void Game::LevelBuilder::CreateObservers(dae::Scene* pScene)
{
	auto livesTextObject = new dae::GameObject("Lives Text", pScene);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/Pang.ttf", 22);
	auto text = std::make_unique<dae::TextComponent>(livesTextObject, "Lives", font);

	auto players = pScene->GetRoot()->GetChildrenByTag("Player");
	for (auto player : players)
	{
		auto livesDisplay = std::make_unique<LivesDisplayComponent>(livesTextObject, player->GetComponent<LivesComponent>(), text.get());
		player->AddComponent(std::move(livesDisplay));

		player->GetComponent<LivesComponent>()->AddObserver(player->GetComponent<LivesDisplayComponent>());
	}

	livesTextObject->AddComponent(std::move(text));
	pScene->Add(livesTextObject);
}
