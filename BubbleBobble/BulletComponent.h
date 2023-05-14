#pragma once
#include "Component.h"

namespace Game
{
	class BulletComponent : public dae::Component
	{
	public:
		BulletComponent(dae::GameObject* pObject);
		virtual ~BulletComponent() = default;
		BulletComponent(const BulletComponent& other) = delete;
		BulletComponent(BulletComponent&& other) noexcept = delete;
		BulletComponent& operator=(const BulletComponent& other) = delete;
		BulletComponent& operator=(BulletComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};
	};
}