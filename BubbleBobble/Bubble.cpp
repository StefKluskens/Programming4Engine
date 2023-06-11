#include "Bubble.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
#include "Scene.h"
#include "MaitaComponent.h"
#include "ZenChanComponent.h"

Game::Bubble::Bubble(dae::GameObject* pObject, std::vector<dae::ColliderComponent*> enemies, bool lookingLeft)
	: Component(pObject)
	, m_pEnemies(enemies)
{
	auto bubbleTexture = std::make_unique<dae::TextureComponent>(pObject);
	bubbleTexture->SetTag("RunTexture");
	bubbleTexture->SetTexture("Resources/Bubble/Bubble_Anim.png");
	bubbleTexture->SetIsAnimation(true);

	auto pAnimator = std::make_unique<dae::AnimatorComponent>(pObject, bubbleTexture.get());
	m_pAnimator = pAnimator.get();
	pObject->AddComponent(std::move(pAnimator));
	SetAnimator();

	auto animation = std::make_unique<dae::Animation>("Bubble", bubbleTexture.get(), 48, 48, 3, 0.33f);
	AddAnimation(std::move(animation));

	GetOwner()->AddComponent(std::move(bubbleTexture));

	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(48);
	rect.w = static_cast<int>(48);
	auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
	m_pCollider = collider.get();
	m_pCollider->AddIgnoreTag("Player");
	m_pCollider->AddIgnoreTag("Fries");
	m_pCollider->AddIgnoreTag("Watermelon");
	m_pCollider->SetNeedsGroundCheck(false);
	pObject->AddComponent(std::move(collider));

	auto rb = std::make_unique<dae::RigidBody>(pObject, m_pCollider);
	m_pRigidbody = rb.get();
	pObject->AddComponent(std::move(rb));

	if (lookingLeft)
	{
		m_MoveSpeed *= -1;
	}
}

void Game::Bubble::Render() const
{
}

void Game::Bubble::Update(float deltaTime)
{
	if (m_MoveOnX)
	{
		m_MoveXTimer += deltaTime;

		if (m_MoveXTimer >= m_MoveXTimerMax)
		{
			m_MoveOnX = false;
		}
	}

	if (!m_Bursting)
	{
		m_BurstTimer += deltaTime;
		if (m_BurstTimer > m_BurstTimerMax)
		{
			Burst();
		}
		else
		{
			m_pAnimator->SetAnimation(m_AnimationMap["Bubble"].get());
		}

		auto enemy = m_pCollider->CheckCollisionOnVector(m_pEnemies);
		if (enemy)
		{
			auto maita = enemy->GetComponent<MaitaComponent>();
			if (maita)
			{
				if (maita->GetState() != MaitaState::Bubble)
				{
					maita->SetState(MaitaState::Bubble);
				}
			}
			else
			{
				auto zenChan = enemy->GetComponent<ZenChanComponent>();
				if (zenChan->GetState() != ZenChanState::Bubble)
				{
					zenChan->SetState(ZenChanState::Bubble);
				}
			}

			Burst();
		}
	}
}

void Game::Bubble::FixedUpdate(float /*deltaTime*/)
{
	if (m_MoveOnX)
	{
		auto velocity = m_pRigidbody->GetVelocity();
		glm::vec3 newPosition = glm::vec3(m_InputDir.x * m_MoveSpeed, velocity.y, 0.0f);

		m_pRigidbody->SetVelocity(newPosition);
	}
	else
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		if (pos.y > m_UpperLimit && !m_Bursting)
		{
			m_Movement.y = m_FloatRate;
		}
		else
		{
			m_Movement.y = 0.f;
		}

		m_pRigidbody->SetVelocity(m_Movement);
	}
}

void Game::Bubble::AddAnimation(std::unique_ptr<dae::Animation> animation)
{
	m_AnimationMap.insert(std::make_pair(animation->Name, std::move(animation)));
}

void Game::Bubble::SetAnimator()
{
	m_pAnimator = GetOwner()->GetComponent<dae::AnimatorComponent>();
}

void Game::Bubble::Burst()
{
	if (!m_Bursting)
	{
		//m_pCollider->SetEnabled(false);
		m_Bursting = true;
		m_Movement = glm::vec3();

		GetOwner()->GetScene()->Remove(GetOwner());
	}
}
