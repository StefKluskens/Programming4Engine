#pragma once
#include "Component.h"
#include <map>
#include <vector>
#include <memory>
#include "Animation.h"

namespace dae
{
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
	enum  class ZenChanState
	{
		Run,
		Die,
		Bubble
	};

	class ZenChanComponent : public dae::Component
	{
	public:
		ZenChanComponent(dae::GameObject* pObject);
		virtual ~ZenChanComponent() = default;
		ZenChanComponent(const ZenChanComponent& other) = delete;
		ZenChanComponent(ZenChanComponent&& other) noexcept = delete;
		ZenChanComponent& operator=(const ZenChanComponent& other) = delete;
		ZenChanComponent& operator=(ZenChanComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

		dae::TextureComponent* GetTexture() const { return m_pCurrentTexture; }
		dae::TextureComponent* GetTexture(const std::string& name) const;

		void AddAnimation(std::unique_ptr<dae::Animation> animation);
		void SetAnimator();

		std::map<std::string, std::unique_ptr<dae::Animation>>& GetAnimationMap() { return m_AnimationMap; }

		void SetState(ZenChanState nextState);
		ZenChanState GetState() const { return m_CurrentState; }

		void AddPlayer(dae::GameObject* pPlayer);

		void SetInBubble(bool inBubble) { m_InBubble = inBubble; }
		bool GetInBubble() const { return m_InBubble; }

	private:
		void HandleMovement(float deltaTime);
		void BubbleMovement(float deltaTime);

		void HandleAI();

		void Die();

		ZenChanState m_CurrentState{};

		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidbody{};
		dae::TextureComponent* m_pCurrentTexture{};

		std::map<std::string, std::unique_ptr<dae::Animation>> m_AnimationMap{};
		dae::AnimatorComponent* m_pAnimator{};

		float m_MoveSpeed{ 100.0f };
		float m_JumpForce{ 500.0f };
		float m_FloatSpeed{ -75.0f };

		float m_xDstMax{ 100.0f };
		float m_yDstMax{ 30.0f };

		glm::vec2 m_InputDir{};

		std::vector<dae::GameObject*> m_pPLayers{};

		bool m_InBubble{ false };

		int m_WindowHeight{ 672 };
	};
}