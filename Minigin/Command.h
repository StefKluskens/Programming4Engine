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

#pragma region MoveCommands

class MoveCommand : public Command
{
public:
	MoveCommand(GameObject* pActor);
	void Execute(float deltaTime) override;

private:
	TransformComponent* m_pTransform{};
	glm::vec2 m_Direction{ 0.f,-1.f };
	float speed = 50.f;
};

class MoveUp : public Command
{
public:
	MoveUp(GameObject* pActor);
	void Execute(float deltaTime) override;

private:
	TransformComponent* m_pTransform{};
	glm::vec2 m_Direction{ 0.f,-1.f };
	float speed = 50.f;
};

class MoveDown : public Command
{
public:
	MoveDown(GameObject* pActor);
	void Execute(float deltaTime) override;

private:
	TransformComponent* m_pTransform{};
	glm::vec2 m_Direction{ 0.f,1.f };
	float speed = 50.f;
};

class MoveLeft : public Command
{
public:
	TransformComponent* m_pTransform{};
	MoveLeft(GameObject* pActor);
	void Execute(float deltaTime) override;

private:
	glm::vec2 m_Direction{ -1.f,0.f };
	float speed = 50.f;
};

class MoveRight : public Command
{
public:
	TransformComponent* m_pTransform{};
	MoveRight(GameObject* pActor);
	void Execute(float deltaTime) override;

private:
	glm::vec2 m_Direction{ 1.f,0.f };
	float speed = 50.f;
};

#pragma endregion MoveCommands