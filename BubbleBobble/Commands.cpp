#include "Command.h"
#include "Commands.h"
#include "Transform.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "RigidBody.h"
#include "PlayerComponent.h"
#include "ShootComponent.h"

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

Game::ScoreCommand::ScoreCommand(dae::Scene* pScene, dae::GameObject* pObject, dae::Command::ButtonState action)
	: dae::Command(pScene)
	, m_pObject(pObject)
	, m_Action(action)
{
}

void Game::ScoreCommand::Execute(float /*deltaTime*/)
{
	m_pObject->GetComponent<Game::ScoreComponent>()->AddScore(100);
}

Game::ShootCommand::ShootCommand(dae::Scene* pScene, dae::GameObject* pObject, ShootComponent* pShootComponent, dae::Command::ButtonState action)
	: dae::Command(pScene)
	, m_pObject(pObject)
	, m_Action(action)
	, m_pShootComponent(pShootComponent)
{
}

void Game::ShootCommand::Execute(float /*deltaTime*/)
{
	std::cout << "Shoot\n";
	m_pShootComponent->Shoot();
}
