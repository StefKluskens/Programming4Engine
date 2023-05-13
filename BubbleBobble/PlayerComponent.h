#pragma once
#include "Component.h"
#include <string>

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

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

		void SetInputDirection(glm::vec3 direction);

	private:
		void HandleMovement(float deltaTime);

		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidbody{};
		dae::TextureComponent* m_pTexture{};
		dae::sound_system* m_pSoundSytem;

		bool m_isPlayer1{ true };

		float m_MoveSpeed{ 100.0f };
		float m_JumpForce{ 400.f };

		glm::vec3 m_InputDir{};
	};
}