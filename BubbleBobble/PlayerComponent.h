#pragma once
#include "Component.h"
#include "Animation.h"
#include <string>
#include <vector>
#include <memory>

namespace dae
{
	class Command;
	class ColliderComponent;
	class RigidBody;
	class TextureComponent;
	class sound_system;
}

namespace Game
{
	class PlayerComponent : public dae::Component
	{
	public:
		PlayerComponent(dae::GameObject* pObject, bool isPLayer1, bool hasCollider, bool hasRB);
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

		bool m_isPlayer1{ true };

		float m_MoveSpeed{ 100.0f };
		float m_JumpForce{ 200.f };

		glm::vec3 m_InputDir{};
	};
}