#include "PlayerComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Commands.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include <memory>

Game::PlayerComponent::PlayerComponent(dae::GameObject* pObject, bool isPLayer1, bool hasCollider, bool hasRB)
	: Component(pObject)
	, m_isPlayer1(isPLayer1)
{
	auto texture = std::make_unique<dae::TextureComponent>(pObject);
	if (isPLayer1)
	{
		texture->SetTexture("Resources/Bob.png");
	}
	else
	{
		texture->SetTexture("Resources/Bub.png");
	}
	GetOwner()->AddComponent(std::move(texture));

	m_pTexture = GetOwner()->GetComponent<dae::TextureComponent>();

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
		auto rb = std::make_unique<dae::RigidBody>(GetOwner());
		GetOwner()->AddComponent(std::move(rb));

		m_pRigidbody = GetOwner()->GetComponent<dae::RigidBody>();
		if (m_pRigidbody && m_pCollider)
		{
			m_pCollider->SetRigidbody(m_pRigidbody);
		}
	}

	auto& input = dae::InputManager::GetInstance();
	int controllerIndex = dae::InputManager::GetInstance().AddXBoxController();

	if (m_isPlayer1)
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_W, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_A, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_D, std::move(pMoveCommand));

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadLeft, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadRight, std::move(pMoveCommand), controllerIndex);
	}
	else
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_UP, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_LEFT, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_RIGHT, std::move(pMoveCommand));

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadLeft, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadRight, std::move(pMoveCommand), controllerIndex);
	}
}

void Game::PlayerComponent::Render() const
{
}

void Game::PlayerComponent::Update(float /*deltaTime*/)
{
}

void Game::PlayerComponent::FixedUpdate(float /*deltaTime*/)
{
	m_pCollider->CollisionCheck();
	m_pCollider->DoGroundCheck();
}