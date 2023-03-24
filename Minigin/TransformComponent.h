#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* pGameObject);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		const glm::vec3& GetPosition() const;
		void SetPosition(const float x, const float y, const float z);
		void SetPosition(glm::vec3 pos);
		void AddPosition(glm::vec3 pos);

		const float GetRotation();
		void SetRotation(float angle);
		void AddRotation(float rot);

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		void SetPositionDirty();
		void UpdateWorldPosition();

	private:
		glm::vec3 m_LocalPos;
		glm::vec3 m_WorldPos;

		float m_Rotation{};

		bool m_IsPosDirty{ true };

		GameObject* m_pParent{};
	};
}