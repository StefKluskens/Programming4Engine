#pragma once
#include "Component.h"
#include "Animation.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace dae
{
	class Command;
	class ColliderComponent;
	class RigidBody;
	class TextureComponent;
	class sound_system;
	class AnimatorComponent;
	class Scene;
}

namespace Game
{
	class PlayerComponent : public dae::Component
	{
	public:
		PlayerComponent(dae::Scene* pScene, dae::GameObject* pObject, bool isPLayer1, bool hasCollider, bool hasRB, int controllerIndex1, int controllerIndex2);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float deltaTime) override;

		void SetInputDirection(glm::vec3 direction);

	private:
		void HandleMovement(float deltaTime);

		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidbody{};
		dae::TextureComponent* m_pCurrentTexture{};
		dae::sound_system* m_pSoundSytem;

		std::vector<std::unique_ptr<dae::Animation>> m_pAnimations{};
		std::map<std::string, std::unique_ptr<dae::Animation>> m_AnimationMap{};
		dae::AnimatorComponent* m_pAnimator;

		bool m_isPlayer1{ true };

		float m_MoveSpeed{ 100.0f };
		float m_JumpForce{ 250.f };

		glm::vec3 m_InputDir{};
	};
}