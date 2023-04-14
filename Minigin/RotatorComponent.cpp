#include "RotatorComponent.h"
#include "GameObject.h"
#include <memory>

dae::RotatorComponent::RotatorComponent(GameObject* pObject, float radius, float rotSpeedRad)
	: Component(pObject)
	, m_Radius(radius)
	, m_RotSpeed(rotSpeedRad)
{
	m_pOwner = GetOwner();
	m_Center = m_pOwner->GetParent()->GetTransform()->GetLocalPosition();
}

dae::RotatorComponent::RotatorComponent(RotatorComponent&& other) noexcept
	: Component(std::move(other))
{
	m_Radius = std::move(other.m_Radius);
	m_RotSpeed = std::move(other.m_RotSpeed);

	m_pOwner = std::move(other.m_pOwner);
}

void dae::RotatorComponent::Render() const
{
}

void dae::RotatorComponent::Update(float deltaTime)
{
	m_CurrentRadians += m_RotSpeed * deltaTime;

	float newXPosRot{ cosf(m_CurrentRadians) * m_Radius };
	float newYPosRot{ sinf(m_CurrentRadians) * m_Radius };

	glm::vec3 newPos{ newXPosRot + m_Center.x, newYPosRot + m_Center.y, 0 };

	m_pOwner->SetPosition(newPos);
}
