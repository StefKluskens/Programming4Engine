#include "PlayerBuilder.h"
#include <fstream>
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "AnimatorComponent.h"
#include "Animation.h"
#include "ZenChanComponent.h"
#include "MaitaComponent.h"
#include <sstream>

void Game::PlayerBuilder::BuildPlayer(std::string levelFile, dae::Scene* pScene, int controllerIndex1, int controllerIndex2, int gameMode)
{
	m_pFile = dae::ResourceManager::GetInstance().LoadTextFile(levelFile);
	std::string line;

	m_pScene = pScene;

	if (gameMode == 0)
	{
		m_MaxNrOfPlayers = 1;
	}

	if (m_pFile->is_open())
	{
		while (!m_pFile->eof())
		{
			std::getline(*m_pFile, line);

			if (m_NrOfPlayers < m_MaxNrOfPlayers && line.rfind("Player ", 0) == 0)
			{
				BuildPlayerComponent(line, controllerIndex1, controllerIndex2);
				AddPlayerToEnemies();
			}
			else if (line.rfind("Anim ", 0) == 0)
			{
				BuildAnimations(line);
			}
		}
	}

	m_NrOfPlayers = 0;
}

void Game::PlayerBuilder::BuildPlayerComponent(std::string line, int controllerIndex1, int controllerIndex2)
{
	m_pPlayerObject = new dae::GameObject("Player", m_pScene);
	m_pPlayerObject->SetTag("Player");

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

	m_pPlayerObject->SetName(name);
	m_pPlayerObject->SetPosition(xPos, yPos);

	auto playerComp = std::make_unique<PlayerComponent>(m_pScene, m_pPlayerObject, isPlayer1, hasCollider, hasRB, controllerIndex1, controllerIndex2);
	m_pPlayerComponent = playerComp.get();
	m_pPlayerObject->AddComponent(std::move(playerComp));

	auto pAnimator = std::make_unique<dae::AnimatorComponent>(m_pPlayerObject, m_pPlayerComponent->GetTexture());
	m_pPlayerObject->AddComponent(std::move(pAnimator));
	m_pPlayerComponent->SetAnimator();

	m_pScene->Add(m_pPlayerObject);

	++m_NrOfPlayers;
}

void Game::PlayerBuilder::BuildAnimations(std::string line)
{
	auto player1 = m_pScene->GetRoot()->GetChildByName("Player 1");
	auto player2 = m_pScene->GetRoot()->GetChildByName("Player 2");

	if (player1)
	{
		PlayerAnimator(player1, line);
		//SetPlayerAnimation(player1);
		player1->GetComponent<PlayerComponent>()->SetState(PlayerState::Idle);
	}
	
	if (player2)
	{
		PlayerAnimator(player2, line);
		//SetPlayerAnimation(player2);
		player2->GetComponent<PlayerComponent>()->SetState(PlayerState::Idle);
	}
}

void Game::PlayerBuilder::PlayerAnimator(dae::GameObject* player, std::string line)
{
	std::stringstream ss(line);

	std::string animId, animName;
	int frameWidth, frameHeight, nrOfFrames;
	float frameTime;

	//Anim data (name, width, height, nrOfFrames, frameTime)
	ss >> animId >> animName >> frameWidth >> frameHeight >> nrOfFrames >> frameTime;

	auto playerComp = player->GetComponent<PlayerComponent>();

	std::string textureName = animName + "Texture";
	auto texture = playerComp->GetTexture(textureName);
	texture->SetIsAnimation(true);
	auto animation = std::make_unique<dae::Animation>(animName, texture, frameWidth, frameHeight, nrOfFrames, frameTime);

	playerComp->AddAnimation(std::move(animation));
}

void Game::PlayerBuilder::SetPlayerAnimation(dae::GameObject* player)
{
	auto animator = player->GetComponent<dae::AnimatorComponent>();
	auto playerComp = player->GetComponent<PlayerComponent>();
	
	if (!playerComp->GetAnimationMap().empty())
	{
		const auto& firstAnimation = playerComp->GetAnimationMap().begin()->second.get();
		animator->SetAnimation(firstAnimation);
	}
}

void Game::PlayerBuilder::AddPlayerToEnemies()
{
	auto enemies = m_pScene->GetRoot()->GetChildrenByTag("Enemy");

	for (auto enemy : enemies)
	{
		auto zenChan = enemy->GetComponent<ZenChanComponent>();
		if (zenChan)
		{
			zenChan->AddPlayer(m_pPlayerObject);
		}
		else 
		{
			auto maita = enemy->GetComponent<MaitaComponent>();
			maita->AddPlayer(m_pPlayerObject);
		}
	}
}
