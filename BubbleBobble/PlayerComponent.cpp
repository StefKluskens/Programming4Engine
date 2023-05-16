#include "PlayerComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "ResourceManager.h"
#include "ShootComponent.h"
#include "AnimatorComponent.h"
#include <memory>

Game::PlayerComponent::PlayerComponent(dae::GameObject* pObject, bool isPLayer1, bool hasCollider, bool hasRB)
	: Component(pObject)
	, m_isPlayer1(isPLayer1)
{
	auto texture = std::make_unique<dae::TextureComponent>(pObject);
	if (isPLayer1)
	{
		texture->SetTexture("Resources/Player/Idle_Anim.png");
	}
	else
	{
		texture->SetTexture("Resources/Bub.png");
	}
	GetOwner()->AddComponent(std::move(texture));

	m_pTexture = GetOwner()->GetComponent<dae::TextureComponent>();
	m_pTexture->SetIsAnimation(true);

	auto pAnimator = std::make_unique<dae::AnimatorComponent>(pObject, m_pTexture, 48, 48, 2, 0.5f);
	GetOwner()->AddComponent(std::move(pAnimator));

	if (hasCollider)
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		SDL_Rect rect;
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);
		rect.h = static_cast<int>(m_pTexture->GetSize().y);
		rect.w = static_cast<int>(m_pTexture->GetSize().x);
		auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
		GetOwner()->AddComponent(std::move(collider));

		m_pCollider = GetOwner()->GetComponent<dae::ColliderComponent>();
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

	/*auto pShootComponent = std::make_unique<ShootComponent>(pObject);
	GetOwner()->AddComponent(std::move(pShootComponent));

	auto shootComponent = GetOwner()->GetComponent<ShootComponent>();*/
	

	m_pSoundSytem = &dae::ServiceLocator::GetSoundSystem();
	m_pSoundSytem->AddSound(dae::ResourceManager::GetInstance().GetAudioPath("Audio/Jump.wav"));

	auto& input = dae::InputManager::GetInstance();
	int controllerIndex = dae::InputManager::GetInstance().AddXBoxController();

	if (m_isPlayer1)
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(SDL_SCANCODE_W, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_A, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_D, std::move(pMoveCommand));

		/*auto pShootCommand = std::make_unique<Game::ShootCommand>(pObject, shootComponent, dae::Command::ButtonState::IsDown);
		input.AddCommand(SDL_SCANCODE_J, std::move(pShootCommand));*/

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(dae::XBoxController::ControllerButton::DPadLeft, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(dae::XBoxController::ControllerButton::DPadRight, std::move(pMoveCommand), controllerIndex);

		/*pShootCommand = std::make_unique<Game::ShootCommand>(pObject, shootComponent, dae::Command::ButtonState::IsDown);
		input.AddCommand(dae::XBoxController::ControllerButton::ButtonB, std::move(pShootCommand), controllerIndex);*/

	}
	else
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(SDL_SCANCODE_UP, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_LEFT, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_RIGHT, std::move(pMoveCommand));

		/*auto pShootCommand = std::make_unique<Game::ShootCommand>(pObject, shootComponent, dae::Command::ButtonState::IsDown);
		input.AddCommand(SDL_SCANCODE_KP_0, std::move(pShootCommand));*/

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsDown);
		input.AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(dae::XBoxController::ControllerButton::DPadLeft, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, this, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(dae::XBoxController::ControllerButton::DPadRight, std::move(pMoveCommand), controllerIndex);

		/*pShootCommand = std::make_unique<Game::ShootCommand>(pObject, shootComponent, dae::Command::ButtonState::IsDown);
		input.AddCommand(dae::XBoxController::ControllerButton::ButtonB, std::move(pShootCommand), controllerIndex);*/
	}
}

void Game::PlayerComponent::Render() const
{
}

void Game::PlayerComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
}

void Game::PlayerComponent::FixedUpdate(float /*deltaTime*/)
{
}

void Game::PlayerComponent::SetInputDirection(glm::vec3 direction)
{
	m_InputDir = direction;
}

void Game::PlayerComponent::HandleMovement(float deltaTime)
{
	glm::vec3 velocity = glm::vec3{ m_InputDir.x * m_MoveSpeed * deltaTime, m_pRigidbody->GetVelocity().y, 0.f };
	m_pRigidbody->SetVelocity(velocity);

	if (m_pRigidbody->IsGrounded() && m_InputDir.y != 0.f)
	{
		m_pSoundSytem->Play(0, 1.0f);

		velocity = glm::vec3{ m_pRigidbody->GetVelocity().x, m_InputDir.y * m_JumpForce * deltaTime, 0.f };
		m_pRigidbody->SetVelocity(velocity);
	}

	m_InputDir = glm::vec3{ 0.f,0.f,0.f };
}
