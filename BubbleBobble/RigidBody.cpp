#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"

Game::RigidBody::RigidBody(dae::GameObject* pObject)
	: Component(pObject)
{
	m_pTransform = pObject->GetTransform();
}

Game::RigidBody::RigidBody(RigidBody&& other) noexcept
	: Component(std::move(other))
{
}

void Game::RigidBody::FixedUpdate(float deltaTime)
{
	m_pTransform->SetLocalPosition(m_pTransform->GetLocalPosition() + (m_Direction * deltaTime));

	//Find better place for this
	m_Direction = glm::vec3{ 0.f,0.f,0.f };
}

void Game::RigidBody::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}
