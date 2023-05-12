#pragma once
#include "Component.h"
#include "SDL_rect.h"
#include <vector>

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

		std::vector<GameObject*> CollisionCheck();
		void DoGroundCheck();

		void SetMoveable(bool isMoveable);
		void SetNeedsCollision(bool needsCollisionCheck);
		bool NeedsToCheckCollision() const;
		void SetNeedsGroundCheck(bool needsGroundCheck);
		bool NeedsToCheckGroundCollision() const;

		SDL_Rect GetRect() const;

		void SetRigidbody(dae::RigidBody* pRigidbody);

	private:
		bool HandleCollision(ColliderComponent* other);

		SDL_Rect m_Rect;
		Transform* m_pObjectTransform;
		bool m_Enabled = true;
		bool m_NeedsToCheckCollision = true;
		bool m_IsMoveable = true;
		bool m_NeedsToDoGroundCheck = true;

		RigidBody* m_pRigidBody;

		std::vector<GameObject*> m_HitObjects{};
	};
}