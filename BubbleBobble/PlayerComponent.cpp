#include "PlayerComponent.h"
#include <memory>
#include "GameObject.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "AnimatorComponent.h"
#include "Scene.h"
#include "MaitaComponent.h"
#include "ZenChanComponent.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"
#include "Bubble.h"

Game::PlayerComponent::PlayerComponent(dae::Scene* pScene, dae::GameObject* pObject, bool isPLayer1, bool hasCollider, bool hasRB, int controllerIndex1, int controllerIndex2)
	: Component(pObject)
	, m_pScene(pScene)
	, m_isPlayer1(isPLayer1)
{
	auto idleTexture = std::make_unique<dae::TextureComponent>(pObject);
	idleTexture->SetTag("IdleTexture");
	auto runTexture = std::make_unique<dae::TextureComponent>(pObject);
	runTexture->SetTag("RunTexture");
	auto dieTexture = std::make_unique<dae::TextureComponent>(pObject);
	dieTexture->SetTag("DieTexture");
	if (isPLayer1)
	{
		idleTexture->SetTexture("Resources/Player/Idle_AnimBob.png");
		runTexture->SetTexture("Resources/Player/Run_AnimBob.png");
		dieTexture->SetTexture("Resources/Player/Death_AnimBob.png");
	}
	else
	{
		idleTexture->SetTexture("Resources/Player/Idle_AnimBub.png");
		runTexture->SetTexture("Resources/Player/Run_AnimBub.png");
		dieTexture->SetTexture("Resources/Player/Death_AnimBub.png");
	}

	runTexture->SetTextureVisibility(false);
	dieTexture->SetTextureVisibility(false);

	GetOwner()->AddComponent(std::move(idleTexture));
	GetOwner()->AddComponent(std::move(runTexture));
	GetOwner()->AddComponent(std::move(dieTexture));

	m_pBubbleTexture = std::make_unique<dae::TextureComponent>(pObject);
	m_pBubbleTexture->SetTexture("Resources/Bubble/Bubble_Anim.png");
	m_pBubbleTexture->SetIsAnimation(true);

	if (hasCollider)
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		SDL_Rect rect;
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);
		rect.h = static_cast<int>(48);
		rect.w = static_cast<int>(48);
		auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
		GetOwner()->AddComponent(std::move(collider));

		m_pCollider = GetOwner()->GetComponent<dae::ColliderComponent>();

		m_pCollider->AddIgnoreTag("Roof");
	}

	if (hasRB)
	{
		auto rb = std::make_unique<dae::RigidBody>(GetOwner(), m_pCollider);
		GetOwner()->AddComponent(std::move(rb));

		m_pRigidbody = GetOwner()->GetComponent<dae::RigidBody>();
		if (m_pRigidbody && m_pCollider)
		{
			m_pCollider->SetRigidbody(m_pRigidbody);
		}
	}

	m_pSoundSytem = &dae::ServiceLocator::GetSoundSystem();
	m_pSoundSytem->AddSound(dae::ResourceManager::GetInstance().GetAudioPath("Audio/Jump.wav"));
	m_pSoundSytem->AddSound(dae::ResourceManager::GetInstance().GetAudioPath("Audio/Shoot.wav"));
	m_pSoundSytem->AddSound(dae::ResourceManager::GetInstance().GetAudioPath("Audio/Death.wav"));

	auto& input = dae::InputManager::GetInstance();

	if (m_isPlayer1)
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_W, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_A, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_D, std::move(pMoveCommand));

		auto pShootCommand = std::make_unique<Game::ShootCommand>(pScene, pObject, this, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_J, std::move(pShootCommand));

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex1);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadLeft, std::move(pMoveCommand), controllerIndex1);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadRight, std::move(pMoveCommand), controllerIndex1);

		pShootCommand = std::make_unique<Game::ShootCommand>(pScene, pObject, this, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::ButtonB, std::move(pShootCommand), controllerIndex1);

	}
	else
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_UP, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_LEFT, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_RIGHT, std::move(pMoveCommand));

		/*auto pShootCommand = std::make_unique<Game::ShootCommand>(pScene, pObject, shootComponent, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), SDL_SCANCODE_KP_0, std::move(pShootCommand));*/

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex2);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadLeft, std::move(pMoveCommand), controllerIndex2);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pScene, pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::DPadRight, std::move(pMoveCommand), controllerIndex2);

		/*pShootCommand = std::make_unique<Game::ShootCommand>(pScene, pObject, shootComponent, dae::Command::ButtonState::IsDown);
		input.AddCommand(pScene->GetName(), dae::XBoxController::ControllerButton::ButtonB, std::move(pShootCommand), controllerIndex2);*/
	}

	for (auto enemy : pScene->GetRoot()->GetChildrenByTag("Enemy"))
	{
		m_pEnemies.push_back(enemy->GetComponent<dae::ColliderComponent>());
	}

	m_pScoreCommand = std::make_unique<ScoreCommand>(pScene, pObject);

	auto scoreComponent = std::make_unique<ScoreComponent>(pObject);
	m_pScoreComponent = scoreComponent.get();
	GetOwner()->AddComponent(std::move(scoreComponent));

	auto livesComponent = std::make_unique<LivesComponent>(pObject, 3);
	m_pLivesComponent = livesComponent.get();
	GetOwner()->AddComponent(std::move(livesComponent));
}

void Game::PlayerComponent::Render() const
{
}

void Game::PlayerComponent::Update(float deltaTime)
{
	switch (m_CurrentState)
	{
	case Game::PlayerState::Idle:
		if (abs(m_Velocity.x) > 0.f)
		{
			SetState(PlayerState::Run);
		}
		break;
	case Game::PlayerState::Run:
		if (abs(m_Velocity.x) == 0)
		{
			SetState(PlayerState::Idle);
		}
		break;
	case Game::PlayerState::Shoot:
		m_ShootCoolTimer += deltaTime;
		if (m_ShootCoolTimer > m_ShootCoolTimerMax)
		{ 
			SetState(PlayerState::Idle);
		}
		break;
	case Game::PlayerState::Die:
		if (m_pAnimator->IsAnimationFinished())
		{
			m_pAnimator->ResetAnimationFinished();
			SetState(PlayerState::Idle);
		}
		break;
	default:
		break;
	}

	//Only do something if enemy is already in bubble state
	//bullet puts enemy in bubble
	auto enemy = m_pCollider->CheckCollisionOnVector(m_pEnemies);
	if (enemy)
	{
		auto maita = enemy->GetComponent<MaitaComponent>();
		if (maita)
		{
			OnCollideMaita(maita);
		}
		else
		{
			auto zenChan = enemy->GetComponent<ZenChanComponent>();
			OnCollideZenChan(zenChan);
		}
	}

	Invincible(deltaTime);
}

void Game::PlayerComponent::FixedUpdate(float deltaTime)
{
	HandleMovement(deltaTime);
}

void Game::PlayerComponent::SetInputDirection(glm::vec3 direction)
{
	m_InputDir = direction;
}

dae::TextureComponent* Game::PlayerComponent::GetTexture(const std::string& name) const
{
	return GetOwner()->GetComponent<dae::TextureComponent>(name);
}

void Game::PlayerComponent::AddAnimation(std::unique_ptr<dae::Animation> animation)
{
	m_AnimationMap.insert(std::make_pair(animation->Name, std::move(animation)));
}

void Game::PlayerComponent::SetAnimator()
{
	m_pAnimator = GetOwner()->GetComponent<dae::AnimatorComponent>();
}

void Game::PlayerComponent::SetState(PlayerState nextState)
{
	m_CurrentState = nextState;

	switch (nextState)
	{
	case Game::PlayerState::Idle:
		m_pAnimator->SetAnimation(m_AnimationMap["Idle"].get());
		break;
	case Game::PlayerState::Run:
		m_pAnimator->SetAnimation(m_AnimationMap["Run"].get());
		break;
	case Game::PlayerState::Shoot:
		ShootBubble();
		break;
	case Game::PlayerState::Die:
	{
		if (!m_IsDead && !m_Invincible)
		{
			m_pSoundSytem->Play(2, 1.0f);

			m_pAnimator->SetAnimation(m_AnimationMap["Die"].get());

			auto velocity = m_pRigidbody->GetVelocity();
			m_pRigidbody->SetVelocity(glm::vec3(0.0f, velocity.y, 0.0f));

			m_pLivesComponent->Die();
			m_IsDead = true;
		}
		break;
	}
	default:
		break;
	}
}

void Game::PlayerComponent::HandleMovement(float deltaTime)
{
	if (m_IsDead)
	{
		m_Invincible = true;
		m_IsDead = false;
		GetOwner()->SetPosition(m_InitialPosition);
		m_pRigidbody->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	m_Velocity = glm::vec3{ m_InputDir.x * m_MoveSpeed * deltaTime, m_pRigidbody->GetVelocity().y, 0.f };
	m_pRigidbody->SetVelocity(m_Velocity);

	if (m_pRigidbody->IsGrounded() && m_InputDir.y != 0.f)
	{
		m_pSoundSytem->Play(0, 1.0f);

		m_Velocity = glm::vec3{ m_pRigidbody->GetVelocity().x, m_InputDir.y * m_JumpForce * deltaTime, 0.f };
		m_pRigidbody->SetVelocity(m_Velocity);
	}

	m_InputDir = glm::vec3{ 0.f,0.f,0.f };
}

void Game::PlayerComponent::Invincible(float deltaTime)
{
	if (m_Invincible)
	{
		if (m_InvincibleTimer < m_MaxInvincibleTimer)
		{
			m_InvincibleTimer += deltaTime;
		}
		else
		{
			m_Invincible = false;
			m_InvincibleTimer = 0.0f;
		}
	}
}

void Game::PlayerComponent::ShootBubble()
{
	if (m_CurrentState == PlayerState::Shoot && !m_Invincible)
	{
		m_pSoundSytem->Play(1, 1.0f);

		auto bubbleObject = new dae::GameObject("Bubble", m_pScene);
		bubbleObject->SetTag("Bubble");
		bubbleObject->SetPosition(GetOwner()->GetTransform()->GetWorldPosition());

		auto bubble = std::make_unique<Bubble>(bubbleObject, m_pEnemies);
		bubbleObject->AddComponent(std::move(bubble));

		m_pScene->Add(bubbleObject);

		m_ShootCoolTimer = 0.0f;
	}
}

void Game::PlayerComponent::SetScoreType(bool isWatermelon)
{
	m_pScoreCommand->SetScoreType(isWatermelon);
	m_pScoreCommand->Execute(0.0f);
}

void Game::PlayerComponent::OnCollideMaita(MaitaComponent* pMaita)
{
	if (pMaita->GetState() == MaitaState::Bubble)
	{
		pMaita->SetState(MaitaState::Die);
	}
	else if(!m_Invincible && pMaita->GetState() == MaitaState::Run)
	{
		SetState(PlayerState::Die);
	}
}

void Game::PlayerComponent::OnCollideZenChan(ZenChanComponent* zenChan)
{
	if (zenChan->GetState() == ZenChanState::Bubble)
	{
		zenChan->SetState(ZenChanState::Die);
	}
	else if (!m_Invincible)
	{
		SetState(PlayerState::Die);
	}
}
