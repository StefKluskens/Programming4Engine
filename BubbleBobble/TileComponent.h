#pragma once
#include "Component.h"

namespace Game
{
	class TileComponent : public dae::Component
	{
	public:
		TileComponent(dae::GameObject* pObject, bool isSmallTile);
		virtual ~TileComponent() = default;
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) noexcept = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};
	};
}