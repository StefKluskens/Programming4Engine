#include "ColliderComponent.h"
#include <SDL_render.h>
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"

dae::ColliderComponent::ColliderComponent(GameObject* pObject, SDL_Rect rect)
	: Component(pObject)
	, m_Rect{rect}
{
	m_pObjectTransform = pObject->GetTransform();
}

dae::ColliderComponent::ColliderComponent(ColliderComponent&& other) noexcept
	: Component(std::move(other))
{
	m_Rect = std::move(other.m_Rect);
	m_pObjectTransform = std::move(other.m_pObjectTransform);
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

void dae::ColliderComponent::CollisionCheck()
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
				}
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
