#pragma once
#include "Component.h"

namespace dae
{
	class Transform : public Component
	{
	public:
		Transform(GameObject* pObject);
		virtual ~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) noexcept;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		void Render() const override {};
		void Update([[maybe_unused]]float deltaTime) override {};

		const glm::vec3 GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();

		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(const glm::vec3& pos) { m_WorldPosition = pos; }
		void SetPositionDirty();

		float GetSpeedForMovement() const { return m_MovementSpeed; }
		void SetSpeedForMovement(float speed) { m_MovementSpeed = speed; }
	private:
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};

		float m_MovementSpeed{ 20.f };
		bool m_PositionIsDirty{ true };
	};
}
