#include "GameObject.h"

namespace dae
{
	enum class ButtonState
	{
		IsDown,
		IsUp,
		IsPressed,
		None
	};

	class Command
	{
	public:
		explicit Command();
		virtual ~Command();
		virtual void Execute(float deltaTime) = 0;
		virtual ButtonState GetButtonState() = 0;
	};


	class MoveCommand : public Command
	{
	public:
		MoveCommand(GameObject* pActor, glm::vec3 direction, float moveSpeed, ButtonState action);
		void Execute(float deltaTime) override;
		ButtonState GetButtonState() override { return m_Action; };
		void SetSpeed(float newSpeed);

	private:
		Transform* m_pTransform{};
		glm::vec3 m_MoveDirection{};
		float speed = 50.f;
		ButtonState m_Action;
	};

	class DieCommand : public Command
	{
	public:
		DieCommand(GameObject* pObject, ButtonState action);
		void Execute(float deltaTime) override;
		ButtonState GetButtonState() override { return m_Action; };

	private:
		GameObject* m_pObject;
		ButtonState m_Action;
	};

	class ScoreCommand : public Command
	{
	public:
		ScoreCommand(GameObject* pObject, ButtonState action);
		void Execute(float deltaTime) override;
		ButtonState GetButtonState() override { return m_Action; };

	private:
		GameObject* m_pObject;
		ButtonState m_Action;
	};
}