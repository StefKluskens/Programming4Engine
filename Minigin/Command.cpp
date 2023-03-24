#include "Command.h"
#include "TransformComponent.h"

Command::Command(GameObject* pActor)
	: m_pActor(pActor)
{
}

Command::~Command()
{
}

#pragma region MoveCommands

MoveUp::MoveUp(GameObject* pActor)
	: Command(pActor)
{
	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}

void MoveUp::Execute(float deltaTime)
{
	std::cout << "Move up executed\n";
	glm::vec3 direction = { m_Direction.x * speed, m_Direction.y * speed,0.f };
	m_pTransform->SetLocalPosition(m_pTransform->GetPosition() + direction * deltaTime);
}

MoveDown::MoveDown(GameObject* pActor)
	: Command(pActor)
{
	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}

void MoveDown::Execute(float deltaTime)
{
	std::cout << "Move down executed\n";
	glm::vec3 direction = { m_Direction.x * speed, m_Direction.y * speed,0.f };
	m_pTransform->SetLocalPosition(m_pTransform->GetPosition() + direction * deltaTime);
}

MoveLeft::MoveLeft(GameObject* pActor)
	: Command(pActor)
{
	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}

void MoveLeft::Execute(float deltaTime)
{
	std::cout << "Move left executed\n";
	glm::vec3 direction = { m_Direction.x * speed, m_Direction.y * speed,0.f };
	m_pTransform->SetLocalPosition(m_pTransform->GetPosition() + direction * deltaTime);
}

MoveRight::MoveRight(GameObject* pActor)
	: Command(pActor)
{
	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}

void MoveRight::Execute(float deltaTime)
{
	std::cout << "Move right executed\n";
	glm::vec3 direction = { m_Direction.x * speed, m_Direction.y * speed,0.f };
	m_pTransform->SetLocalPosition(m_pTransform->GetPosition() + direction * deltaTime);
}

#pragma endregion MoveCommands

MoveCommand::MoveCommand(GameObject* pActor)
	: Command(pActor)
{
	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}

void MoveCommand::Execute(float deltaTime)
{
	glm::vec3 direction = { m_Direction.x * speed, m_Direction.y * speed,0.f };
	m_pTransform->SetLocalPosition(m_pTransform->GetPosition() + direction * deltaTime);
}
