#pragma once
#include <SDL_rect.h>
#include "Component.h"

namespace dae
{
	class Transform;
	class ColliderComponent;

	class RigidBody : public Component
	{
	public:
		RigidBody(GameObject* pObject, ColliderComponent* pCollider);
		virtual ~RigidBody() = default;
		RigidBody(const RigidBody& other) = delete;
		RigidBody(RigidBody&& other) noexcept = delete;
		RigidBody& operator=(const RigidBody& other) = delete;
		RigidBody& operator=(RigidBody&& other) = delete;

		void Render() const override;
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float deltaTime) override;

		void SetDirection(glm::vec3 direction);
		void SetVelocity(glm::vec3 velocity);

		glm::vec3 GetVelocity() const;

		void SetIsGrounded(bool isGrounded);
		bool IsGrounded() const;

		void CheckCollision();

	private:
		glm::vec3 m_Direction{};
		glm::vec3 m_Velocity{};
		Transform* m_pTransform{};

		SDL_Rect m_Rect{};
		ColliderComponent* m_pCollider{};

		bool m_Grounded = false;

		float m_Gravity{ 1000.0f };
		bool m_ApplyGravity{ true };

		bool m_SideCollision{ false };

		bool m_RightCollision{ false };
		bool m_LeftCollision{ false };
	};
}