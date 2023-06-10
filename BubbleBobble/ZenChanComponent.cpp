#include "ZenChanComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
#include "Scene.h"

Game::ZenChanComponent::ZenChanComponent(dae::GameObject* pObject)
	: dae::Component(pObject)
{
	auto runTexture = std::make_unique<dae::TextureComponent>(pObject);
	runTexture->SetTag("RunTexture");
	runTexture->SetTexture("Resources/ZenChan/Run_Anim.png");
	runTexture->SetIsAnimation(true);

	auto pAnimator = std::make_unique<dae::AnimatorComponent>(pObject, runTexture.get());
	pObject->AddComponent(std::move(pAnimator));
	SetAnimator();

	auto animation = std::make_unique<dae::Animation>("Run", runTexture.get(), 45, 48, 4, 0.25f);
	AddAnimation(std::move(animation));

	GetOwner()->AddComponent(std::move(runTexture));

	//Collider
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(48);
	rect.w = static_cast<int>(45);
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

	SetState(ZenChanState::Run);
}

void Game::ZenChanComponent::Render() const
{
}

void Game::ZenChanComponent::Update(float /*deltaTime*/)
{
	
}

void Game::ZenChanComponent::FixedUpdate(float deltaTime)
{
	switch (m_CurrentState)
	{
	case Game::ZenChanState::Run:
		HandleMovement(deltaTime);
		break;
	case Game::ZenChanState::Die:

		break;
	case Game::ZenChanState::Bubble:
		BubbleMovement(deltaTime);
		break;
	default:
		break;
	}
}

dae::TextureComponent* Game::ZenChanComponent::GetTexture(const std::string& name) const
{
	return GetOwner()->GetComponent<dae::TextureComponent>(name);
}

void Game::ZenChanComponent::AddAnimation(std::unique_ptr<dae::Animation> animation)
{
	m_AnimationMap.insert(std::make_pair(animation->Name, std::move(animation)));
}

void Game::ZenChanComponent::SetAnimator()
{
	m_pAnimator = GetOwner()->GetComponent<dae::AnimatorComponent>();
}

void Game::ZenChanComponent::SetState(ZenChanState nextState)
{
	switch (nextState)
	{
	case Game::ZenChanState::Run:
		m_pAnimator->SetAnimation(m_AnimationMap["Run"].get());
		break;
	case Game::ZenChanState::Die:
		break;
	case Game::ZenChanState::Bubble:
		break;
	default:
		break;
	}
}

void Game::ZenChanComponent::AddPlayer(dae::GameObject* pPlayer)
{
	m_pPLayers.push_back(pPlayer);
}

void Game::ZenChanComponent::HandleMovement(float /*deltaTime*/)
{
	HandleAI();

	glm::vec3 velocity = m_pRigidbody->GetVelocity();

	if (m_pRigidbody->IsGrounded())
	{
		m_pRigidbody->SetVelocity(velocity + glm::vec3(velocity.x, m_InputDir.y * m_JumpForce, 0.f));
	}

	velocity = m_pRigidbody->GetVelocity();
	m_pRigidbody->SetVelocity(glm::vec3(m_InputDir.x * m_MoveSpeed, velocity.y, 0.0f));
}

void Game::ZenChanComponent::BubbleMovement(float deltaTime)
{
	m_pRigidbody->SetVelocity(glm::vec3(0.f, m_FloatSpeed * deltaTime, 0.f));
	m_InputDir = glm::vec3();
}

void Game::ZenChanComponent::HandleAI()
{
	//Only do stuff if running and there are players
	if (m_CurrentState == ZenChanState::Run && !m_pPLayers.empty())
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
