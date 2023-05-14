#include "ShootComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TextureComponent.h"
#include "BulletComponent.h"
#include "Scene.h"

Game::ShootComponent::ShootComponent(dae::GameObject* pObject)
	: dae::Component(pObject)
{
}

void Game::ShootComponent::Shoot()
{
	auto pObject = GetOwner();

	auto pBulletObject = new dae::GameObject("Bullet", pObject->GetScene());
	auto pBulletComponent = std::make_unique<BulletComponent>(pObject);
	pBulletObject->AddComponent(std::move(pBulletComponent));

	auto pBulletTexture = std::make_unique<dae::TextureComponent>(pObject);
	//set texture
	auto pTexture = pBulletTexture.get();
	pBulletObject->AddComponent(std::move(pBulletTexture));

	if (pTexture->IsTextureSet())
	{
		auto pos = pObject->GetTransform()->GetLocalPosition();
		SDL_Rect rect;
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);
		rect.h = static_cast<int>(pTexture->GetSize().y);
		rect.w = static_cast<int>(pTexture->GetSize().x);
		auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
		pBulletObject->AddComponent(std::move(collider));
	}

	pObject->GetScene()->Add(pBulletObject);
}