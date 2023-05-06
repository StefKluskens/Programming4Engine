#pragma once
#include "Component.h"
#include "SDL_rect.h"

namespace dae
{
	class Transform;
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(GameObject* pObject, SDL_Rect rect);
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate([[maybe_unused]] float deltaTime) override {};

		bool CollisionCheck();

	private:
		SDL_Rect m_Rect;
		Transform* m_pObjectTransform;
	};
}