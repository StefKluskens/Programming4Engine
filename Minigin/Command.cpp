#include "Command.h"
#include "TransformComponent.h"

Command::Command(GameObject* pActor)
	: m_pActor(pActor)
{
}

Command::~Command()
{
}

MoveCommand::MoveCommand(GameObject* pActor, MoveDirection direction, float moveSpeed)
	: Command(pActor)
	, m_MoveDirection(direction)
	, speed(moveSpeed)
{
	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}

void MoveCommand::Execute(float deltaTime)
{
	glm::vec3 direction = {};

	switch (m_MoveDirection)
	{
	case MoveCommand::MoveDirection::Up:
		direction = { 0.f, -1.f * speed, 0.f };
		break;
	case MoveCommand::MoveDirection::Down:
		direction = { 0.f, 1.f * speed, 0.f };
		break;
	case MoveCommand::MoveDirection::Left:
		direction = { -1.f * speed, 0.f, 0.f };
		break;
	case MoveCommand::MoveDirection::Right:
		direction = { 1.f * speed, 0.f, 0.f };
		break;
	}

	m_pTransform->SetLocalPosition(m_pTransform->GetPosition() + direction * deltaTime);
}

void MoveCommand::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}
