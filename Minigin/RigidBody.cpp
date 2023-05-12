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
	m_Velocity = m_pTransform->GetLocalPosition() + (m_Direction * deltaTime);

	if (m_ApplyGravity && !m_Grounded)
	{
		m_Velocity.y += m_Gravity * deltaTime;
	}

	m_pTransform->SetLocalPosition(m_Velocity);

	//Find better place for this
	m_Direction = glm::vec3{ 0.f,0.f,0.f };
}

void dae::RigidBody::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}

void dae::RigidBody::SetIsGrounded(bool isGrounded)
{
	m_Grounded = isGrounded;
}

bool dae::RigidBody::IsGrounded() const
{
	return m_Grounded;
}

float dae::RigidBody::GetYVelocity() const
{
	return m_Velocity.y;
}

void dae::RigidBody::SetGravity(bool useGravity)
{
	m_ApplyGravity = useGravity;
}
