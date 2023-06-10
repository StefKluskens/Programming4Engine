#include "Command.h"
#include "Commands.h"
#include "Transform.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "RigidBody.h"
#include "PlayerComponent.h"
#include "ShootComponent.h"
#include "BubbleBobble.h"
#include "SceneManager.h"
#include "Scene.h"
#include "AnimatorComponent.h"

Game::MoveCommand::MoveCommand(dae::Scene* pScene, dae::GameObject* pActor, PlayerComponent* pPlayerComponent, glm::vec3 direction, float moveSpeed, dae::Command::ButtonState action)
	: dae::Command(pScene)
	, m_MoveDirection(direction)
	, speed(moveSpeed)
	, m_Action(action)
	, m_pPlayer(pPlayerComponent)
{
	m_pTransform = pActor->GetTransform();
	m_pRigidbody = pActor->GetComponent<dae::RigidBody>();
}

void Game::MoveCommand::Execute(float /*deltaTime*/)
{
	glm::vec3 direction = m_MoveDirection * speed;
	m_pPlayer->SetInputDirection(direction);
}

void Game::MoveCommand::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

Game::DieCommand::DieCommand(dae::Scene* pScene, dae::GameObject* pObject, dae::Command::ButtonState action)
	: dae::Command(pScene)
	, m_pObject(pObject)
	, m_Action(action)
{
}

void Game::DieCommand::Execute(float /*deltaTime*/)
{
	m_pObject->GetComponent<Game::LivesComponent>()->Die();
}

Game::ScoreCommand::ScoreCommand(dae::Scene* pScene, dae::GameObject* pObject)
	: dae::Command(pScene)
	, m_pObject(pObject)
{
}

void Game::ScoreCommand::Execute(float /*deltaTime*/)
{
	m_pObject->GetComponent<Game::ScoreComponent>()->AddScore(m_ScoreAmount);
}

void Game::ScoreCommand::SetScoreType(bool isWaterMelon)
{
	if (isWaterMelon)
	{
		m_ScoreAmount = 100;
	}
	else
	{
		m_ScoreAmount = 200;
	}
}

Game::ShootCommand::ShootCommand(dae::Scene* pScene, dae::GameObject* pObject, PlayerComponent* pPlayerComponent, dae::Command::ButtonState action)
	: dae::Command(pScene)
	, m_pObject(pObject)
	, m_Action(action)
	, m_pPlayer(pPlayerComponent)
{
}

void Game::ShootCommand::Execute(float /*deltaTime*/)
{
	if (m_pPlayer->GetState() != PlayerState::Shoot)
	{
		m_pPlayer->SetState(PlayerState::Shoot);
	}
}

Game::LoadSceneCommand::LoadSceneCommand(dae::Scene* pScene, dae::GameObject* pObject, int gameMode, dae::Command::ButtonState action, BubbleBobble& bubbleBobble, int controllerIndex1, int controllerIndex2)
	: dae::Command(pScene)
	, m_pObject(pObject)
	, m_Action(action)
	, m_GameMode(gameMode)
	, m_BubbleBobble(bubbleBobble)
	, m_Controller1(controllerIndex1)
	, m_Controller2(controllerIndex2)
{
}

void Game::LoadSceneCommand::Execute(float /*deltaTime*/)
{
	BubbleBobble::GameMode gameMode = static_cast<BubbleBobble::GameMode>(m_GameMode);
	m_BubbleBobble.SetGameMode(gameMode);

	if (GetScene()->GetName() == "MainMenu")
	{
		m_BubbleBobble.MainMenuExit(m_Controller1, m_Controller2);
	}

	auto scenes = dae::SceneManager::GetInstance().GetScenes();
	scenes;

	std::cout << "load level0\n";
	switch (gameMode)
	{
	case BubbleBobble::GameMode::SinglePlayer:
		dae::SceneManager::GetInstance().SetActiveScene("Level0");
		break;
	case BubbleBobble::GameMode::MultiPlayer:
		dae::SceneManager::GetInstance().SetActiveScene("Level0");
		break;
	case BubbleBobble::GameMode::Versus:
		std::cout << "Versus\n";
		break;
	default:
		break;
	}
}
