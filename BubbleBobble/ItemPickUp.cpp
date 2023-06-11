#include "ItemPickUp.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "PlayerComponent.h"

Game::ItemPickUp::ItemPickUp(dae::GameObject* pObject, bool isFries, std::vector<dae::GameObject*>& pPlayers)
	: Component(pObject)
	, m_IsFries(isFries)
	, m_pPlayers(pPlayers)
{
	auto pItemTexture = std::make_unique<dae::TextureComponent>(pObject);

	if (isFries)
	{
		pItemTexture->SetTexture("Resources/Item/Fries.png");
		pObject->SetTag("Fries");
	}
	else
	{
		pItemTexture->SetTexture("Resources/Item/Watermelon.png");
		pObject->SetTag("Watermelon");
	}

	pObject->AddComponent(std::move(pItemTexture));

	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(48);
	rect.w = static_cast<int>(48);
	auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
	m_pCollider = collider.get();
	m_pCollider->AddIgnoreTag("Enemy");
	pObject->AddComponent(std::move(collider));

	auto rb = std::make_unique<dae::RigidBody>(pObject, m_pCollider);
	m_pRigidBody = rb.get();
	pObject->AddComponent(std::move(rb));

	for (auto player : m_pPlayers)
	{
		m_pPlayerColliders.push_back(player->GetComponent<dae::ColliderComponent>());
	}
}

void Game::ItemPickUp::Render() const
{
}

void Game::ItemPickUp::Update(float /*deltaTime*/)
{
	auto player = m_pCollider->CheckCollisionOnVector(m_pPlayerColliders);
	if (player)
	{
		auto playerComp = player->GetComponent<PlayerComponent>();
		playerComp->SetScoreType(!m_IsFries);

		GetOwner()->GetScene()->Remove(GetOwner());
	}
}

void Game::ItemPickUp::FixedUpdate(float /*deltaTime*/)
{
}
