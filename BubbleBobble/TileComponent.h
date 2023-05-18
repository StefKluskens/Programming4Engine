#pragma once
#include "Component.h"
#include "SDL_rect.h"

namespace dae
{
	class ColliderComponent;
	class TextureComponent;
}

namespace Game
{
	class TileComponent : public dae::Component
	{
	public:
		TileComponent(dae::GameObject* pObject, bool isSmallTile, int sceneNr);
		virtual ~TileComponent() = default;
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) noexcept = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};

		void SetColliderRow(int nrOfTiles);
		void SetColliderColumn(int nrOfTiles);

	private:
		dae::ColliderComponent* m_pCollider{};
		dae::TextureComponent* m_pTexture{};
	};
}