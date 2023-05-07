#pragma once
#include "Component.h"
#include "SDL_rect.h"

namespace dae
{
	class Transform;
	class RigidBody;
	class GameObject;

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(GameObject* pObject, SDL_Rect rect);
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Render() const override;
		void Update([[maybe_unused]] float deltaTime) override {};
		void FixedUpdate(float deltaTime) override;

		GameObject* CollisionCheck();
		void DoGroundCheck();

		void SetMoveable(bool isMoveable);
		void SetNeedsCollision(bool needsCollisionCheck);

		SDL_Rect GetRect() const;

	private:
		bool HandleCollision(ColliderComponent* other);

		SDL_Rect m_Rect;
		Transform* m_pObjectTransform;
		bool m_Enabled = true;
		bool m_NeedsToCheckCollision = true;
		bool m_IsMoveable = true;

		RigidBody* m_pRigidBody;

		GameObject* m_HitObject{};
	};
}