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

void Game::ColliderComponent::Update(float /*deltaTime*/)
{
	//Move collider with owner
	m_Rect.x = static_cast<int>(m_pObjectTransform->GetWorldPosition().x);
	m_Rect.y = static_cast<int>(m_pObjectTransform->GetWorldPosition().y);

	
}

bool Game::ColliderComponent::CollisionCheck()
{
	return false;
}
