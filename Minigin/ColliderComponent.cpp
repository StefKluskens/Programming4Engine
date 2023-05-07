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
	m_pRigidBody = pObject->GetComponent<RigidBody>();
}

void dae::ColliderComponent::Render() const
{
	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_Rect);

	//Point 1 (centre of object)
	int x1 = (m_Rect.x + m_Rect.w) / 2;
	int y1 = (m_Rect.y + m_Rect.h) / 2;

	//Point 2 (1 px below object)
	int x2 = x1;
	int y2 = m_Rect.y - 1;
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), x1, y1, x2, y2);
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

dae::GameObject* dae::ColliderComponent::CollisionCheck()
{
	//Check if this collider needs to check for collisions
	if (m_NeedsToCheckCollision)
	{
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
				//Check for collision
				if (HandleCollision(collider))
				{
					//Collided
					std::cout << GetOwner()->GetName() << " collided with " << collider->GetOwner()->GetName() << '\n';
					m_HitObject = collider->GetOwner();

					return m_HitObject;
				}
			}
		}
	}

	return nullptr;
}

void dae::ColliderComponent::DoGroundCheck()
{
	//Draw line from center of object towards 1 px beneath object
	//If line intersects with floor, set grounded from RB to true

	//Point 1 (centre of object)
	int x1 = (m_Rect.x + m_Rect.w) / 2;
	int y1 = (m_Rect.y + m_Rect.h) / 2;

	//Point 2 (1 px below object)
	int x2 = x1;
	int y2 = m_Rect.y - 1;

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
				std::cout << "Bottom collision with " << collider->GetOwner()->GetName() << '\n';
			}
		}
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
