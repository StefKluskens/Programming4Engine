#pragma once
#include "Component.h"

namespace dae
{
	class ColliderComponent;
	class Command;
}

namespace Game
{
	class PlayerComponent : public dae::Component
	{
	public:
		PlayerComponent(dae::GameObject* pObject, bool isPLayer1);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

	private:
		dae::ColliderComponent* m_pCollider{};

		bool m_isPlayer1{ true };

		float m_MoveSpeed{ 50.0f };
	};
}