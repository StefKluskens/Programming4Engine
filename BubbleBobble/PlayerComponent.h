#pragma once
#include "Component.h"
#include "Animation.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace dae
{
	class Command;
	class ColliderComponent;
	class RigidBody;
	class TextureComponent;
	class sound_system;
	class AnimatorComponent;
	class Scene;
}

namespace Game
{
	class ScoreCommand;
	class MaitaComponent;
	class ZenChanComponent;
	class LivesComponent;
	class ScoreComponent;

	enum class PlayerState
	{
		Idle,
		Run,
		Shoot,
		Die
	};

	class PlayerComponent : public dae::Component
	{
	public:
		PlayerComponent(dae::Scene* pScene, dae::GameObject* pObject, bool isPLayer1, bool hasCollider, bool hasRB, int controllerIndex1, int controllerIndex2);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

		void SetInputDirection(glm::vec3 direction);

		dae::TextureComponent* GetTexture() const { return m_pCurrentTexture; }
		dae::TextureComponent* GetTexture(const std::string& name) const;

		void AddAnimation(std::unique_ptr<dae::Animation> animation);
		void SetAnimator();

		std::map<std::string, std::unique_ptr<dae::Animation>>& GetAnimationMap() { return m_AnimationMap; }

		void SetState(PlayerState nextState);
		PlayerState GetState() const { return m_CurrentState; }

		void SetInitialPosition(const glm::vec3& pos) { m_InitialPosition = pos; }

		void ShootBubble();

		void SetScoreType(bool isWatermelon);

	private:
		void HandleMovement(float deltaTime);
		void Invincible(float deltaTime);

		void OnCollideMaita(MaitaComponent* pOther);
		void OnCollideZenChan(ZenChanComponent* pOther);

		dae::Scene* m_pScene{};

		dae::ColliderComponent* m_pCollider{};
		dae::RigidBody* m_pRigidbody{};
		dae::TextureComponent* m_pCurrentTexture{};
		dae::sound_system* m_pSoundSytem;

		//std::vector<std::unique_ptr<dae::Animation>> m_pAnimations{};
		std::map<std::string, std::unique_ptr<dae::Animation>> m_AnimationMap{};
		dae::AnimatorComponent* m_pAnimator;

		bool m_isPlayer1{ true };

		float m_MoveSpeed{ 100.0f };
		float m_JumpForce{ 250.f };

		glm::vec3 m_InputDir{};
		glm::vec3 m_Velocity{};

		PlayerState m_CurrentState{};

		std::unique_ptr<ScoreCommand> m_pScoreCommand{};

		std::vector<dae::ColliderComponent*> m_pEnemies{};

		LivesComponent* m_pLivesComponent{};
		ScoreComponent* m_pScoreComponent{};

		glm::vec3 m_InitialPosition{};

		bool m_IsDead{ false };

		bool m_Invincible{ false };
		float m_MaxInvincibleTimer{ 3.0f };
		float m_InvincibleTimer{ 0.0f };

		std::unique_ptr<dae::TextureComponent> m_pBubbleTexture{};

		float m_ShootCoolTimer{};
		float m_ShootCoolTimerMax{ 3.0f };

		bool m_IsLookingLeft{ false };

		int m_WindowHeight{ 672 };
	};
}