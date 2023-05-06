#pragma once
//#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class Transform;
	class GameObject;
}

namespace Game
{
	class RigidBody;

	class MoveCommand : public dae::Command
	{
	public:
		MoveCommand(dae::GameObject* pActor, glm::vec3 direction, float moveSpeed, dae::Command::ButtonState action);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };
		void SetSpeed(float newSpeed);

	private:
		dae::Transform* m_pTransform{};
		glm::vec3 m_MoveDirection{};
		float speed = 50.f;
		dae::Command::ButtonState m_Action;
		RigidBody* m_pRigidbody;
	};

	class DieCommand : public dae::Command
	{
	public:
		DieCommand(dae::GameObject* pObject, dae::Command::ButtonState action);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };

	private:
		dae::GameObject* m_pObject;
		dae::Command::ButtonState m_Action;
	};

	class ScoreCommand : public dae::Command
	{
	public:
		ScoreCommand(dae::GameObject* pObject, dae::Command::ButtonState action);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };

	private:
		dae::GameObject* m_pObject;
		dae::Command::ButtonState m_Action;
	};
}