#pragma once
//#include "Command.h"
#include <glm/glm.hpp>

class BubbleBobble;

namespace dae
{
	class Transform;
	class GameObject;
	class RigidBody;
	class Scene;
}

namespace Game
{
	class PlayerComponent;
	class ShootComponent;

	class MoveCommand : public dae::Command
	{
	public:
		MoveCommand(dae::Scene* pScene, dae::GameObject* pActor, PlayerComponent* pPlayerComponent, glm::vec3 direction, float moveSpeed, dae::Command::ButtonState action);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };
		void SetSpeed(float newSpeed);

	private:
		dae::Transform* m_pTransform{};
		glm::vec3 m_MoveDirection{};
		float speed = 50.f;
		dae::Command::ButtonState m_Action;
		dae::RigidBody* m_pRigidbody;
		PlayerComponent* m_pPlayer;
	};

	class DieCommand : public dae::Command
	{
	public:
		DieCommand(dae::Scene* pScene, dae::GameObject* pObject, dae::Command::ButtonState action);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };

	private:
		dae::GameObject* m_pObject;
		dae::Command::ButtonState m_Action;
	};

	class ScoreCommand : public dae::Command
	{
	public:
		ScoreCommand(dae::Scene* pScene, dae::GameObject* pObject);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return dae::Command::ButtonState::None; };

		void SetScoreType(bool isWaterMelon = true);

	private:
		dae::GameObject* m_pObject;

		int m_ScoreAmount;
	};

	class ShootCommand : public dae::Command
	{
	public:
		ShootCommand(dae::Scene* pScene, dae::GameObject* pObject, PlayerComponent* pPlayerComponent, dae::Command::ButtonState action);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };

	private:
		dae::GameObject* m_pObject;
		dae::Command::ButtonState m_Action;
		PlayerComponent* m_pPlayer{};
	};

	class LoadSceneCommand : public dae::Command
	{
	public:
		LoadSceneCommand(dae::Scene* pScene, dae::GameObject* pObject, int gameMode, dae::Command::ButtonState action, BubbleBobble& bubbleBobble, int controllerIndex1, int controllerIndex2);
		void Execute(float deltaTime) override;
		dae::Command::ButtonState GetButtonState() override { return m_Action; };

	private:
		dae::GameObject* m_pObject;
		dae::Command::ButtonState m_Action;
		int m_GameMode{};
		BubbleBobble& m_BubbleBobble;

		int m_Controller1{};
		int m_Controller2{};
	};
}