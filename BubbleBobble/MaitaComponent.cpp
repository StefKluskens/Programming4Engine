#include "MaitaComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
#include "Scene.h"

Game::MaitaComponent::MaitaComponent(dae::GameObject* pObject)
	: Component(pObject)
{
	auto runTexture = std::make_unique<dae::TextureComponent>(pObject);
	runTexture->SetTag("RunTexture");
	runTexture->SetTexture("Resources/Maita/Run_Anim.png");
	runTexture->SetIsAnimation(true);

	auto pAnimator = std::make_unique<dae::AnimatorComponent>(pObject, runTexture.get());
	pObject->AddComponent(std::move(pAnimator));
	SetAnimator();

	auto animation = std::make_unique<dae::Animation>("Run", runTexture.get(), 48, 48, 4, 0.25f);
	AddAnimation(std::move(animation));

	GetOwner()->AddComponent(std::move(runTexture));

	//Collider
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(48);
	rect.w = static_cast<int>(48);
	auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
	m_pCollider = collider.get();
	GetOwner()->AddComponent(std::move(collider));

	//RigidBody
	auto rb = std::make_unique<dae::RigidBody>(GetOwner(), m_pCollider);
	m_pRigidbody = rb.get();
	GetOwner()->AddComponent(std::move(rb));

	if (m_pRigidbody && m_pCollider)
	{
		m_pCollider->SetRigidbody(m_pRigidbody);
	}

	SetState(MaitaState::Run);
}

void Game::MaitaComponent::Render() const
{
}

void Game::MaitaComponent::Update(float /*deltaTime*/)
{
}

void Game::MaitaComponent::FixedUpdate(float deltaTime)
{
	switch (m_CurrentState)
	{
	case Game::MaitaState::Run:
		HandleMovement(deltaTime);
		break;
	case Game::MaitaState::Die:
		break;
	case Game::MaitaState::Bubble:
		BubbleMovement(deltaTime);
		break;
	case Game::MaitaState::Attack:
		break;
	default:
		break;
	}
}

void Game::MaitaComponent::AddPlayer(dae::GameObject* pPlayer)
{
	m_pPLayers.push_back(pPlayer);
}

void Game::MaitaComponent::SetState(MaitaState nextState)
{
	switch (nextState)
	{
	case Game::MaitaState::Run:
		m_pAnimator->SetAnimation(m_AnimationMap["Run"].get());
		break;
	case Game::MaitaState::Die:
		break;
	case Game::MaitaState::Bubble:
		break;
	case Game::MaitaState::Attack:
		break;
	default:
		break;
	}

	m_CurrentState = nextState;
}

dae::TextureComponent* Game::MaitaComponent::GetTexture(const std::string& name) const
{
	return GetOwner()->GetComponent<dae::TextureComponent>(name);
}

void Game::MaitaComponent::AddAnimation(std::unique_ptr<dae::Animation> animation)
{
	m_AnimationMap.insert(std::make_pair(animation->Name, std::move(animation)));
}

void Game::MaitaComponent::SetAnimator()
{
	m_pAnimator = GetOwner()->GetComponent<dae::AnimatorComponent>();
}

void Game::MaitaComponent::HandleMovement(float /*deltaTime*/)
{
	HandleAI();

	glm::vec3 velocity = m_pRigidbody->GetVelocity();

	if (m_pRigidbody->IsGrounded())
	{
		m_pRigidbody->SetVelocity(velocity + glm::vec3(0.0f, m_InputDir.y * m_JumpForce, 0.0f));
	}

	velocity = m_pRigidbody->GetVelocity();
	m_pRigidbody->SetVelocity(glm::vec3(m_InputDir.x * m_MoveSpeed, velocity.y, 0.0f));
}

void Game::MaitaComponent::BubbleMovement(float /*deltaTime*/)
{
	m_pRigidbody->SetVelocity(glm::vec3(0.0f, m_FloatSpeed, 0.0f));
	m_InputDir = glm::vec2();
}

void Game::MaitaComponent::HandleAI()
{
	if (m_CurrentState == MaitaState::Run && !m_pPLayers.empty())
	{
		const glm::vec3 myPos = GetOwner()->GetTransform()->GetWorldPosition();

		float smallestDistance{};
		glm::vec3 playerPos{};
		bool found = false;
		for (const auto player : m_pPLayers)
		{
			//Check if player is enabled, return if not

			const glm::vec3& pos = player->GetTransform()->GetWorldPosition();
			const float newDist = glm::distance(myPos, pos);

			if (newDist < smallestDistance || !found)
			{
				smallestDistance = newDist;
				playerPos = pos;
				found = true;
			}
		}

		if (!found)
		{
			return;
		}

		if (!m_pRigidbody->IsGrounded())
		{
			return;
		}

		float xDistance = myPos.x - playerPos.x;
		float yDistance = myPos.y - playerPos.y;
		auto velocity = m_pRigidbody->GetVelocity();

		if (abs(yDistance) > m_yDstMax)
		{
			//set shoot required bool to false

			//Player is above
			if (yDistance > 0.0f)
			{
				if (playerPos.x < myPos.x)
				{
					m_InputDir.x = -1.0f;
				}
				else
				{
					m_InputDir.x = 1.0f;
				}

				//Decide if ai has to jump
				if (abs(xDistance) < m_xDstMax)
				{
					m_InputDir.y = -1.f;
				}
				else
				{
					m_InputDir.y = 0.f;
				}
			}
			//Player is below
			else
			{
				m_InputDir.y = 0.f;

				if (m_InputDir.x == 0.f || abs(velocity.x) < 1.f)
				{
					if (rand() % 2)
					{
						m_InputDir.x = -1.0f;
					}
					else
					{
						m_InputDir.x = 1.0f;
					}
				}
			}
		}
		else
		{
			//Player is on the same level
			m_InputDir.y = 0.f;
			if (playerPos.x < myPos.x)
			{
				m_InputDir.x = -1.0f;
			}
			else
			{
				m_InputDir.x = 1.0f;
			}
		}
	}
	else
	{
		m_InputDir = glm::vec2();
	}
}
