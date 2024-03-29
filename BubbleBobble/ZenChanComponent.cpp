#include "ZenChanComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
#include "Scene.h"
#include "ItemPickUp.h"
#include "BubbleBobble.h"

Game::ZenChanComponent::ZenChanComponent(dae::GameObject* pObject)
	: dae::Component(pObject)
{
	auto runTexture = std::make_unique<dae::TextureComponent>(pObject);
	runTexture->SetTag("RunTexture");
	runTexture->SetTexture("Resources/ZenChan/Run_Anim.png");
	runTexture->SetIsAnimation(true);

	auto bubbleTexture = std::make_unique<dae::TextureComponent>(pObject);
	bubbleTexture->SetTag("BubbleTexture");
	bubbleTexture->SetTexture("Resources/ZenChan/Bubble_Anim.png");
	bubbleTexture->SetIsAnimation(true);
	bubbleTexture->SetTextureVisibility(false);

	auto pAnimator = std::make_unique<dae::AnimatorComponent>(pObject, runTexture.get());
	pObject->AddComponent(std::move(pAnimator));
	SetAnimator();

	auto animation = std::make_unique<dae::Animation>("Run", runTexture.get(), 45, 48, 4, 0.25f);
	AddAnimation(std::move(animation));

	animation = std::make_unique<dae::Animation>("Bubble", bubbleTexture.get(), 48, 48, 3, 0.33f);
	AddAnimation(std::move(animation));

	GetOwner()->AddComponent(std::move(runTexture));
	GetOwner()->AddComponent(std::move(bubbleTexture));

	//Collider
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(48);
	rect.w = static_cast<int>(48);
	auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
	m_pCollider = collider.get();
	m_pCollider->AddIgnoreTag("Roof");
	m_pCollider->AddIgnoreTag("Fries");
	m_pCollider->AddIgnoreTag("Watermelon");
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
	if (GetOwner()->GetTransform()->GetWorldPosition().y > m_WindowHeight)
	{
		GetOwner()->SetPosition(GetOwner()->GetTransform()->GetWorldPosition().x, 0.0f);
	}
	else if (GetOwner()->GetTransform()->GetWorldPosition().y < 0.0f)
	{
		BubbleBobble::GetInstance().IncreaseKillNr();
		GetOwner()->GetScene()->Remove(GetOwner());
	}
}

void Game::ZenChanComponent::FixedUpdate(float deltaTime)
{
	switch (m_CurrentState)
	{
	case Game::ZenChanState::Run:
		HandleMovement(deltaTime);
		break;
	case Game::ZenChanState::Die:
		Die();
		break;
	case Game::ZenChanState::Bubble:
		BubbleMovement(deltaTime);
		break;
	default:
		break;
	}
}

void Game::ZenChanComponent::AddPlayer(dae::GameObject* pPlayer)
{
	m_pPLayers.push_back(pPlayer);
}

void Game::ZenChanComponent::SetState(ZenChanState nextState)
{
	switch (nextState)
	{
	case Game::ZenChanState::Run:
		m_pAnimator->SetAnimation(m_AnimationMap["Run"].get());
		break;
	case Game::ZenChanState::Die:
		Die();
		break;
	case Game::ZenChanState::Bubble:
		m_pAnimator->SetAnimation(m_AnimationMap["Bubble"].get());
		break;
	default:
		break;
	}

	m_CurrentState = nextState;
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

void Game::ZenChanComponent::HandleMovement(float /*deltaTime*/)
{
	HandleAI();

	glm::vec3 velocity = m_pRigidbody->GetVelocity();

	if (m_pRigidbody->IsGrounded())
	{
		m_pRigidbody->SetVelocity(velocity + glm::vec3(velocity.x, m_InputDir.y * m_JumpForce, 0.f));
	}

	if (m_InputDir.x > 0.1f)
	{
		m_pAnimator->GetTexture()->SetFlip(SDL_FLIP_NONE);
	}
	else if (m_InputDir.x < -0.1f)
	{
		m_pAnimator->GetTexture()->SetFlip(SDL_FLIP_HORIZONTAL);
	}

	velocity = m_pRigidbody->GetVelocity();
	m_pRigidbody->SetVelocity(glm::vec3(m_InputDir.x * m_MoveSpeed, velocity.y, 0.0f));
}

void Game::ZenChanComponent::BubbleMovement(float /*deltaTime*/)
{
	m_pRigidbody->SetVelocity(glm::vec3(0.f, m_FloatSpeed, 0.f));
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

void Game::ZenChanComponent::Die()
{
	auto item = new dae::GameObject("Watermelon", GetOwner()->GetScene());
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	item->SetPosition(pos.x + 30, pos.y - 50);
	auto pItem = std::make_unique<ItemPickUp>(item, false, m_pPLayers);
	item->AddComponent(std::move(pItem));
	GetOwner()->GetScene()->Add(item);

	GetOwner()->GetScene()->Remove(GetOwner());
}
