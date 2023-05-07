#include "PlayerComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Commands.h"

Game::PlayerComponent::PlayerComponent(dae::GameObject* pObject, bool isPLayer1)
	: Component(pObject)
	, m_isPlayer1(isPLayer1)
{
	m_pCollider = pObject->GetComponent <dae::ColliderComponent>();

	auto& input = dae::InputManager::GetInstance();
	int controllerIndex = dae::InputManager::GetInstance().AddXBoxController();

	if (m_isPlayer1)
	{
		//Keyboard commands
		auto pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_W, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, 1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_S, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_A, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_D, std::move(pMoveCommand));

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, 1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadDown, std::move(pMoveCommand), controllerIndex);

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

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, 1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_DOWN, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ -1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_LEFT, std::move(pMoveCommand));

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 1.0f, 0.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		input.AddCommand(SDL_SCANCODE_RIGHT, std::move(pMoveCommand));

		//Controller commands
		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, -1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadUp, std::move(pMoveCommand), controllerIndex);

		pMoveCommand = std::make_unique<Game::MoveCommand>(pObject, glm::vec3{ 0.0f, 1.0f, 0.0f }, m_MoveSpeed, dae::Command::ButtonState::IsPressed);
		dae::InputManager::GetInstance().AddCommand(dae::XBoxController::ControllerButton::DPadDown, std::move(pMoveCommand), controllerIndex);

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
	//m_pCollider->CollisionCheck();
	m_pCollider->DoGroundCheck();
}
