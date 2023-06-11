#pragma once
#include "Component.h"
#include <map>
#include <memory>
#include "Animation.h"
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
	class Bubble : public dae::Component
	{
	public:
		Bubble(dae::GameObject* pObject, std::vector<dae::ColliderComponent*> enemies);
		virtual ~Bubble() = default;
		Bubble(const Bubble& other) = delete;
		Bubble(Bubble&& other) noexcept = delete;
		Bubble& operator=(const Bubble& other) = delete;
		Bubble& operator=(Bubble&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

		void AddAnimation(std::unique_ptr<dae::Animation> animation);
		void SetAnimator();

	private:
		void Burst();

		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidbody{};
		dae::TextureComponent* m_pCurrentTexture{};

		std::map<std::string, std::unique_ptr<dae::Animation>> m_AnimationMap{};
		dae::AnimatorComponent* m_pAnimator{};

		float m_BurstTimer{};
		float m_BurstTimerMax{ 7.0f };
		bool m_Bursting{ false };

		glm::vec3 m_Movement{};
		float m_MoveSpeed{ 200.0f };
		float m_FloatRate{ -50.0f };
		bool m_MovesLeft{ false };
		float m_UpperLimit{ 192.0f };

		float m_xMaxDistance{ 10.0f };
		bool m_MoveOnX{ true };
		float m_MoveXTimer{ 0.0f };
		float m_MoveXTimerMax{ 1.0f };

		glm::vec2 m_InputDir{ 1.0f,0.0f };


		std::vector<dae::ColliderComponent*> m_pEnemies{};
	};
}