#pragma once
#include "GameObject.h"

using namespace dae;

class Command
{
public:
	explicit Command(GameObject* pActor);
	virtual ~Command();
	virtual void Execute() = 0;

protected:
	GameObject* GetActor() { return m_pActor; }

private:
	GameObject* m_pActor;
};

class MoveCommand : public Command
{
public:
	void Execute() override;

private:
	glm::vec2 m_Direction;
	float speed;
};