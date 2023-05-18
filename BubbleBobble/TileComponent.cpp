#include "TileComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"

Game::TileComponent::TileComponent(dae::GameObject* pObject, bool isSmallTile, int sceneNr)
	: Component(pObject)
{
	auto pTextureComp = std::make_unique<dae::TextureComponent>(pObject);

	if (sceneNr == 0)
	{
		if (isSmallTile)
		{
			pTextureComp->SetTexture("Resources/Tiles/0Small.png");
		}
		else
		{
			pTextureComp->SetTexture("Resources/Tiles/0Big.png");
		}
	}
	else if (sceneNr == 1)
	{
		if (isSmallTile)
		{
			pTextureComp->SetTexture("Resources/Tiles/1Small.png");
		}
		else
		{
			pTextureComp->SetTexture("Resources/Tiles/1Big.png");
		}
	}
	else if (sceneNr == 2)
	{
		if (isSmallTile)
		{
			pTextureComp->SetTexture("Resources/Tiles/2Small.png");
		}
		else
		{
			pTextureComp->SetTexture("Resources/Tiles/2Big.png");
		}
	}	

	m_pTexture = pTextureComp.get();

	GetOwner()->AddComponent(std::move(pTextureComp));
}

void Game::TileComponent::SetColliderRow(int nrOfTiles)
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(m_pTexture->GetSize().y);
	rect.w = static_cast<int>(m_pTexture->GetSize().x * nrOfTiles);
	auto collider = std::make_unique<dae::ColliderComponent>(GetOwner(), rect);
	m_pCollider = collider.get();
	GetOwner()->AddComponent(std::move(collider));
}

void Game::TileComponent::SetColliderColumn(int nrOfTiles)
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(m_pTexture->GetSize().y * nrOfTiles);
	rect.w = static_cast<int>(m_pTexture->GetSize().x);
	auto collider = std::make_unique<dae::ColliderComponent>(GetOwner(), rect);
	m_pCollider = collider.get();
	GetOwner()->AddComponent(std::move(collider));
}
