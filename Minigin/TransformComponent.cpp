#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pGameObject)
	: Component(pGameObject)
{
}

void dae::TransformComponent::Render() const
{
}

void dae::TransformComponent::Update([[maybe_unused]]float deltaTime)
{
}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return m_position;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3{ x,y,z };
}
