#pragma once
#include "Component.h"

namespace dae
{
	class Transform;

	class RigidBody : public Component
	{
	public:
		RigidBody(GameObject* pObject);
		virtual ~RigidBody() = default;
		RigidBody(const RigidBody& other) = delete;
		RigidBody(RigidBody&& other) noexcept;
		RigidBody& operator=(const RigidBody& other) = delete;
		RigidBody& operator=(RigidBody&& other) = delete;

		void Render() const override {};
		void Update([[maybe_unused]] float deltaTime) override {};
		void FixedUpdate(float deltaTime) override;

		void SetDirection(glm::vec3 direction);

	private:
		glm::vec3 m_Direction{};
		glm::vec3 m_Velocity{};
		Transform* m_pTransform{};

		bool m_Grounded = false;

		float m_Gravity{ 10.0f };
	};
}