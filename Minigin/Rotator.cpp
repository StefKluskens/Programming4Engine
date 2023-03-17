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
	glm::vec3 pos{ m_CenterPoint };

	auto pParent = GetGameObject()->GetParent();
	
	if (m_RotateAroundParent && pParent)
	{
		//Rotate around parent gameobject
		auto parentTransform = pParent->GetComponent<TransformComponent>();
		pos = parentTransform->GetPosition();
		
	}

	const float x = pos.x + m_Radius * cos(angle);
	const float y = pos.y + m_Radius * sin(angle);
	pos = glm::vec3(x, y, 0.0f);

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

void dae::Rotator::ShouldRotateAroundParent(bool rotateAroundParent)
{
	m_RotateAroundParent = rotateAroundParent;
}
