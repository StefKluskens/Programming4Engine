#include "ColliderComponent.h"
#include <SDL_render.h>
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "RigidBody.h"

dae::ColliderComponent::ColliderComponent(GameObject* pObject, SDL_Rect rect)
	: Component(pObject)
	, m_Rect{rect}
{
	m_pObjectTransform = pObject->GetTransform();
}

void dae::ColliderComponent::Render() const
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_Rect);
}

void dae::ColliderComponent::FixedUpdate(float /*deltaTime*/)
{
	if (m_IsMoveable)
	{
		//Move collider with owner
		auto pos = m_pObjectTransform->GetWorldPosition();
		m_Rect.x = static_cast<int>(pos.x);
		m_Rect.y = static_cast<int>(pos.y);
	}
}

std::vector<dae::GameObject*> dae::ColliderComponent::CollisionCheck()
{
	//Check if this collider needs to check for collisions
	if (m_NeedsToCheckCollision)
	{
		//Get all colliders from the scene
		auto colliders = SceneManager::GetInstance().GetActiveScene()->GetColliders();

		m_HitObjects.clear();

		for (auto collider : colliders)
		{
			//Avoid self collision
			if (collider == this)
			{
				continue;
			}

			//Check if collider is enabled
			if (collider->m_Enabled)
			{
				//Check for collision
				if (HandleCollision(collider))
				{
					m_HitObjects.push_back(collider->GetOwner());
				}
			}
		}
	}

	return m_HitObjects;
}

void dae::ColliderComponent::DoGroundCheck()
{
	if (m_pRigidBody)
	{
		//Draw line from center of object towards 1 px beneath object
		//If line intersects with floor, set grounded from RB to true

		m_pRigidBody->SetIsGrounded(false);

		//Point 1 (centre of object)
		int x1 = m_Rect.x + (m_Rect.w / 2);
		int y1 = m_Rect.y + (m_Rect.h / 2);

		//Point 2 (1 px below object)
		int x2 = x1;
		int y2 = m_Rect.y + m_Rect.h + 3;

		//Get all colliders from the scene
		auto colliders = SceneManager::GetInstance().GetActiveScene()->GetColliders();

		for (auto collider : colliders)
		{
			//Avoid self collision
			if (collider == this)
			{
				continue;
			}

			//Check if collider is enabled
			if (collider->m_Enabled)
			{
				SDL_Rect rect = collider->GetRect();

				if (SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2))
				{
					m_pRigidBody->SetIsGrounded(true);
				}
			}
		}
	}
	else
	{
		std::cout << "No rigidbody attached to " << GetOwner()->GetName() << '\n';
	}
}

void dae::ColliderComponent::SetMoveable(bool isMoveable)
{
	m_IsMoveable = isMoveable;
}

void dae::ColliderComponent::SetNeedsCollision(bool needsCollisionCheck)
{
	m_NeedsToCheckCollision = needsCollisionCheck;
}

SDL_Rect dae::ColliderComponent::GetRect() const
{
	return m_Rect;
}

void dae::ColliderComponent::SetRigidbody(dae::RigidBody* pRigidbody)
{
	m_pRigidBody = pRigidbody;
}

bool dae::ColliderComponent::HandleCollision(ColliderComponent* other)
{
	if ((m_Rect.x + m_Rect.w) < other->m_Rect.x || (other->m_Rect.x + other->m_Rect.w) < m_Rect.x)
	{
		return false;
	}

	if (m_Rect.y > (other->m_Rect.y + other->m_Rect.h) || other->m_Rect.y > (m_Rect.y + m_Rect.h))
	{
		return false;
	}

	return true;
}
