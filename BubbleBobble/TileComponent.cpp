#include "TileComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"

Game::TileComponent::TileComponent(dae::GameObject* pObject, bool isSmallTile)
	: Component(pObject)
{
	auto pTextureComp = std::make_unique<dae::TextureComponent>(pObject);

	if (isSmallTile)
	{
		pTextureComp->SetTexture("Resources/Tiles/Small.png");
	}
	else
	{
		pTextureComp->SetTexture("Resources/Tiles/Big.png");
	}
	

	auto pTexture = pTextureComp.get();

	GetOwner()->AddComponent(std::move(pTextureComp));

	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(pTexture->GetSize().y);
	rect.w = static_cast<int>(pTexture->GetSize().x);
	auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
	GetOwner()->AddComponent(std::move(collider));
}