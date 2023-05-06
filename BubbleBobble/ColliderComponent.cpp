#include "ColliderComponent.h"
#include <SDL_render.h>
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

Game::ColliderComponent::ColliderComponent(dae::GameObject* pObject, SDL_Rect rect)
	: Component(pObject)
	, m_Rect{rect}
{
	m_pObjectTransform = pObject->GetTransform();
}

Game::ColliderComponent::ColliderComponent(ColliderComponent&& other) noexcept
	: Component(std::move(other))
{
	m_Rect = std::move(other.m_Rect);
	m_pObjectTransform = std::move(other.m_pObjectTransform);
}

void Game::ColliderComponent::Render() const
{
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &m_Rect);
}

void Game::ColliderComponent::FixedUpdate(float /*deltaTime*/)
{
	//Move collider with owner
	auto pos = m_pObjectTransform->GetWorldPosition();
	m_Rect.x = static_cast<int>(pos.x);
	m_Rect.y = static_cast<int>(pos.y);

	
}

bool Game::ColliderComponent::HandleCollision(ColliderComponent* other)
{
	if (!m_Enabled)
	{
		return false;
	}

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
