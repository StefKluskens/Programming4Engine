#include "Command.h"
#include "Commands.h"
#include "Transform.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "RigidBody.h"
#include "PlayerComponent.h"

Game::MoveCommand::MoveCommand(dae::GameObject* pActor, PlayerComponent* pPlayerComponent, glm::vec3 direction, float moveSpeed, dae::Command::ButtonState action)
	: dae::Command()
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

Game::DieCommand::DieCommand(dae::GameObject* pObject, dae::Command::ButtonState action)
	: dae::Command()
	, m_pObject(pObject)
	, m_Action(action)
{
}

void Game::DieCommand::Execute([[maybe_unused]] float deltaTime)
{
	m_pObject->GetComponent<Game::LivesComponent>()->Die();
}

Game::ScoreCommand::ScoreCommand(dae::GameObject* pObject, dae::Command::ButtonState action)
	: dae::Command()
	, m_pObject(pObject)
	, m_Action(action)
{
}

void Game::ScoreCommand::Execute([[maybe_unused]] float deltaTime)
{
	m_pObject->GetComponent<Game::ScoreComponent>()->AddScore(100);
}