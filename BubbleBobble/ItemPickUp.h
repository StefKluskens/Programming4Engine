#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class RigidBodyComponent;
	class GameObject;
	class Scene;
	class ColliderComponent;
	class RigidBody;
	class TextureComponent;
	class AnimatorComponent;
}

namespace Game
{
	class ItemPickUp : public dae::Component
	{
	public:
		ItemPickUp(dae::GameObject* pObject, bool isFries, std::vector<dae::GameObject*>& pPlayers);
		virtual ~ItemPickUp() = default;
		ItemPickUp(const ItemPickUp& other) = delete;
		ItemPickUp(ItemPickUp&& other) noexcept = delete;
		ItemPickUp& operator=(const ItemPickUp& other) = delete;
		ItemPickUp& operator=(ItemPickUp&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

	private:
		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidBody{};

		bool m_IsFries{ false };

		std::vector<dae::GameObject*> m_pPlayers{};
		std::vector<dae::ColliderComponent*> m_pPlayerColliders{};
	};
}