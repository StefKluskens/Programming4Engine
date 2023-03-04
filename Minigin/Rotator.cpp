#include "Rotator.h"
#include "TransformComponent.h"

dae::Rotator::Rotator(GameObject* pGameObject)
	: Component(pGameObject)
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}

void dae::Rotator::Render() const
{
}

void dae::Rotator::Update(float deltaTime)
{
	const float angle = m_pTransform->GetRotation() + m_Speed * deltaTime;

	const float x = m_CenterPoint.x + m_Radius * cos(angle);
	const float y = m_CenterPoint.y + m_Radius * sin(angle);
	const glm::vec3 pos = glm::vec3(x, y, 0.0f);

	m_pTransform->SetPosition(pos);
	m_pTransform->SetRotation(angle);
}

void dae::Rotator::SetRadiusSpeed(float radius, float speed)
{
	m_Radius = radius;
	m_Speed = speed;
}

void dae::Rotator::SetCenterPoint(const glm::vec3& center)
{
	m_CenterPoint = center;
}