#pragma once
#include "Component.h"

namespace dae
{
	class Transform;
}

namespace Game
{
	class RigidBody : public dae::Component
	{
	public:
		RigidBody(dae::GameObject* pObject);
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
		dae::Transform* m_pTransform{};

		float m_Gravity{ 1200.0f };
	};
}