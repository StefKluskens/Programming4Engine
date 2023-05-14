#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;
}

namespace Game
{
	class ShootComponent : public dae::Component
	{
	public:
		ShootComponent(dae::GameObject* pObject);
		virtual ~ShootComponent() = default;
		ShootComponent(const ShootComponent& other) = delete;
		ShootComponent(ShootComponent&& other) noexcept = delete;
		ShootComponent& operator=(const ShootComponent& other) = delete;
		ShootComponent& operator=(ShootComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};

		void Shoot();
	};
}