#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"

dae::RigidBody::RigidBody(GameObject* pObject)
	: Component(pObject)
{
	m_pTransform = pObject->GetTransform();
}

dae::RigidBody::RigidBody(RigidBody&& other) noexcept
	: Component(std::move(other))
{
}

void dae::RigidBody::FixedUpdate(float deltaTime)
{
	auto pos = m_pTransform->GetLocalPosition() + (m_Direction * deltaTime);

	if (!m_Grounded)
	{
		//pos.y += m_Gravity * deltaTime;
	}

	m_pTransform->SetLocalPosition(pos);

	//Find better place for this
	m_Direction = glm::vec3{ 0.f,0.f,0.f };
}

void dae::RigidBody::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}
