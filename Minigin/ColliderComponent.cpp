#include "ColliderComponent.h"
#include <SDL_render.h>
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

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

void dae::ColliderComponent::Update(float /*deltaTime*/)
{
	//Move collider with owner
	m_Rect.x = static_cast<int>(m_pObjectTransform->GetWorldPosition().x);
	m_Rect.y = static_cast<int>(m_pObjectTransform->GetWorldPosition().y);

	
}

bool dae::ColliderComponent::CollisionCheck()
{
	return false;
}
