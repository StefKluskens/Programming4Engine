#include "Command.h"
#include "Transform.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"

dae::Command::Command()
{
}

dae::Command::~Command()
{
}

dae::MoveCommand::MoveCommand(dae::GameObject* pActor, glm::vec3 direction, float moveSpeed, ButtonState action)
	: Command()
	, m_MoveDirection(direction)
	, speed(moveSpeed)
	, m_Action(action)
{
	m_pTransform = pActor->GetTransform();
}

void dae::MoveCommand::Execute(float deltaTime)
{
	glm::vec3 direction = m_MoveDirection * speed;

	m_pTransform->SetLocalPosition(m_pTransform->GetLocalPosition() + (direction * deltaTime));
}

void dae::MoveCommand::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

dae::DieCommand::DieCommand(GameObject* pObject, ButtonState action)
	: Command()
	, m_pObject(pObject)
	, m_Action(action)
{
}

void dae::DieCommand::Execute([[maybe_unused]]float deltaTime)
{
	m_pObject->GetComponent<Game::LivesComponent>()->Die();
}

dae::ScoreCommand::ScoreCommand(GameObject* pObject, ButtonState action)
	: Command()
	, m_pObject(pObject)
	, m_Action(action)
{
}

void dae::ScoreCommand::Execute([[maybe_unused]] float deltaTime)
{
	m_pObject->GetComponent<Game::ScoreComponent>()->AddScore(100);
}
