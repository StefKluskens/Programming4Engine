#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Scene.h"

dae::RigidBody::RigidBody(GameObject* pObject, ColliderComponent* pCollider)
	: Component(pObject)
{
	m_pTransform = pObject->GetTransform();
	m_pCollider = pCollider;
}

void dae::RigidBody::Render() const
{
}

void dae::RigidBody::FixedUpdate(float deltaTime)
{
	auto pos = m_pTransform->GetLocalPosition();

	if (!m_Grounded)
	{
		m_Velocity.y += m_Gravity * deltaTime;
	}

	pos += m_Velocity * deltaTime;
	GetOwner()->SetPosition(pos);

	CheckCollision();
}

void dae::RigidBody::SetDirection(glm::vec3 direction)
{
	m_Direction = direction;
}

void dae::RigidBody::SetVelocity(glm::vec3 velocity)
{
	m_Velocity = velocity;
}

glm::vec3 dae::RigidBody::GetVelocity() const
{
	return m_Velocity;
}

void dae::RigidBody::SetIsGrounded(bool isGrounded)
{
	m_Grounded = isGrounded;
}

bool dae::RigidBody::IsGrounded() const
{
	return m_Grounded;
}

void dae::RigidBody::CheckCollision()
{
	if (!m_pCollider->GetEnabled())
	{
		return;
	}

	auto pos = m_pTransform->GetLocalPosition();

	m_Rect = m_pCollider->GetRect();
	std::vector<ColliderComponent*> colliders = GetOwner()->GetScene()->GetColliders();

	for (auto it = colliders.begin(); it != colliders.end(); ++it) {
		if (*it == m_pCollider) 
		{
			colliders.erase(it);
			break;
		}
	}

	//Floor Collision
	if (m_Velocity.y > 0.f)
	{
		int x1 = m_Rect.x + (m_Rect.w / 2);
		int y1 = m_Rect.y + (m_Rect.h / 2);

		int x2 = x1;
		int y2 = m_Rect.y + m_Rect.h + 3;

		m_Grounded = false;

		for (size_t i = 0; i < colliders.size(); ++i)
		{
			auto ignoreTags = m_pCollider->GetIgnoreTags();
			auto it = std::find(ignoreTags.begin(), ignoreTags.end(), colliders[i]->GetOwner()->GetTag());
			if (it != ignoreTags.end())
			{
				continue;
			}

			SDL_Rect rect = colliders[i]->GetRect();
			if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2))
			{
				m_Grounded = true;

				auto bottomCollision = colliders[i]->GetOwner();
				auto bottomYPos = bottomCollision->GetTransform()->GetLocalPosition().y;

				pos.y = bottomYPos - m_Rect.h;
				m_Velocity.y = 1.f;
				break;
			}
		}

		GetOwner()->SetPosition(pos);
	}
	else
	{
		m_Grounded = false;
	}

	//Left col
	int x1 = int(m_Rect.x + m_Rect.w * 0.5f);
	int y1 = int(m_Rect.y + m_Rect.h * 0.5f);
	int x2 = int(m_Rect.x);
	int y2 = y1;

	float offset = pos.x - float(x2);

	for (size_t i = 0; i < colliders.size(); ++i)
	{
		SDL_Rect rect = colliders[i]->GetRect();
		if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2))
		{
			pos.x = x1 + offset;
			m_Velocity.x = 0.0f;

			break;
		}
	}

	//Right col
	x1 = int(m_Rect.x + m_Rect.w * 0.5f);
	y1 = int(m_Rect.y + m_Rect.h * 0.5f);
	x2 = int(m_Rect.x + m_Rect.w + 1);
	y2 = y1;

	offset = pos.x - (float)x2 + 1.f;

	for (size_t i = 0; i < colliders.size(); ++i)
	{
		SDL_Rect rect = colliders[i]->GetRect();
		if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2))
		{
			pos.x = x1 + offset;
			m_Velocity.x = 0.0f;

			break;
		}
	}


	GetOwner()->SetPosition(pos);
}
