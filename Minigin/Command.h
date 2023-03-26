#pragma once
#include "GameObject.h"

using namespace dae;

class Command
{
public:
	explicit Command(GameObject* pActor);
	virtual ~Command();
	virtual void Execute(float deltaTime) = 0;

protected:
	GameObject* GetActor() { return m_pActor; }

private:
	GameObject* m_pActor;
};


class MoveCommand : public Command
{
public:
	enum class MoveDirection
	{
		Up,
		Down,
		Left,
		Right
	};

	MoveCommand(GameObject* pActor, MoveDirection direction, float moveSpeed);
	void Execute(float deltaTime) override;
	void SetSpeed(float newSpeed);

private:
	TransformComponent* m_pTransform{};
	glm::vec2 m_Direction{ 0.f,-1.f };
	MoveDirection m_MoveDirection{};
	float speed = 50.f;
};