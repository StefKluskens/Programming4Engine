#pragma once
#include "Component.h"
#include <map>
#include <vector>
#include <memory>
#include "Animation.h"

namespace dae
{
	class Texture2D;
	class RigidBodyComponent;
	class GameObject;
	class Scene;
	class ColliderComponent;
	class RigidBody;
	class TextureComponent;
	class AnimatorComponent;
}

namespace Game
{
	enum  class MaitaState
	{
		Run,
		Die,
		Bubble,
		Attack
	};

	class MaitaComponent : public dae::Component
	{
	public:
		MaitaComponent(dae::GameObject* pObject);
		virtual ~MaitaComponent() = default;
		MaitaComponent(const MaitaComponent& other) = delete;
		MaitaComponent(MaitaComponent&& other) noexcept = delete;
		MaitaComponent& operator=(const MaitaComponent& other) = delete;
		MaitaComponent& operator=(MaitaComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

		void AddPlayer(dae::GameObject* pPlayer);

		void SetState(MaitaState nextState);
		MaitaState GetState() const { return m_CurrentState; }

		dae::TextureComponent* GetTexture() const { return m_pCurrentTexture; }
		dae::TextureComponent* GetTexture(const std::string& name) const;

		void AddAnimation(std::unique_ptr<dae::Animation> animation);
		void SetAnimator();

		std::map<std::string, std::unique_ptr<dae::Animation>>& GetAnimationMap() { return m_AnimationMap; }

		void Die();

	private:
		void HandleMovement(float deltaTime);
		void BubbleMovement(float deltaTime);

		void HandleAI();

		MaitaState m_CurrentState{};

		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidbody{};
		dae::TextureComponent* m_pCurrentTexture{};

		std::map<std::string, std::unique_ptr<dae::Animation>> m_AnimationMap{};
		dae::AnimatorComponent* m_pAnimator{};

		glm::vec2 m_InputDir{};

		float m_MoveSpeed{ 100.0f };
		float m_JumpForce{ 500.0f };
		float m_FloatSpeed{ -75.0f };

		float m_xDstMax{ 100.0f };
		float m_yDstMax{ 30.0f };

		std::vector<dae::GameObject*> m_pPLayers{};
	};
}