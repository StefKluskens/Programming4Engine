#pragma once
#include "Component.h"

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
		void SetPosition(float x, float y, float z);

	private:
		glm::vec3 m_position;
	};
}