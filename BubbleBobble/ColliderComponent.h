#pragma once
#include "Component.h"
#include "SDL_rect.h"

namespace dae
{
	class Transform;
}

namespace Game
{
	class ColliderComponent : public dae::Component
	{
	public:
		ColliderComponent(dae::GameObject* pObject, SDL_Rect rect);
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Render() const override;
		void Update([[maybe_unused]] float deltaTime) override {};
		void FixedUpdate(float deltaTime) override;

	private:
		bool HandleCollision(ColliderComponent* other);

		SDL_Rect m_Rect;
		dae::Transform* m_pObjectTransform;
		bool m_Enabled = true;
	};
}