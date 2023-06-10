#include "Bubble.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "RigidBody.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
#include "Scene.h"

Game::Bubble::Bubble(dae::GameObject* pObject, dae::TextureComponent* pTexture, std::vector<dae::ColliderComponent*> enemies)
	: Component(pObject)
	, m_pEnemies(enemies)
{
	auto texture = std::make_unique<dae::TextureComponent>(pObject);
	texture->SetTexture("Resources/Bubble/Bubble_Anim.png");
	//texture->SetIsAnimation(true);
	pObject->AddComponent(std::move(texture));

	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.h = static_cast<int>(48);
	rect.w = static_cast<int>(48);
	auto collider = std::make_unique<dae::ColliderComponent>(pObject, rect);
	m_pCollider = collider.get();
	m_pCollider->AddIgnoreTag("Player");
	pObject->AddComponent(std::move(collider));

	auto rb = std::make_unique<dae::RigidBody>(pObject, m_pCollider);
	m_pRigidbody = rb.get();
	pObject->AddComponent(std::move(rb));

	auto animator = std::make_unique<dae::AnimatorComponent>(pObject, pTexture);
	pObject->AddComponent(std::move(animator));
	SetAnimator();

	auto animation = std::make_unique<dae::Animation>("Bubble", pTexture, 48, 48, 3, 0.33f);
	AddAnimation(std::move(animation));

	m_pAnimator->SetAnimation(nullptr);
}

void Game::Bubble::Render() const
{
}

void Game::Bubble::Update(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	if (abs(m_Movement).x < m_xMaxDistance && pos.y > m_UpperLimit && !m_Bursting)
	{
		m_Movement.y = m_FloatRate;
	}
	else
	{
		m_Movement.y = 0.f;
	}

	m_pRigidbody->SetVelocity(m_Movement);

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
	}

	auto enemy = m_pCollider->CheckCollisionOnVector(m_pEnemies);
	if (enemy)
	{
		GetOwner()->GetScene()->Remove(enemy);
	}
}

void Game::Bubble::FixedUpdate(float deltaTime)
{
	if (m_MovesLeft)
	{
		if (m_Movement.x < 0.f)
		{
			m_Movement.x += deltaTime * m_SlowDownRate;
		}
		else
		{
			m_Movement.x = 0.f;
		}
	}
	else
	{
		if (m_Movement.x > 0.f)
		{
			m_Movement.x -= deltaTime * m_SlowDownRate;
		}
		else
		{
			m_Movement.x = 0.f;
		}
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
		//m_pAnimator->SetAnimation(m_AnimationMap["Poof"].get());
		/*m_pCollider->AddIgnoreTag("Maita");
		m_pCollider->AddIgnoreTag("Player");*/
		m_Bursting = true;
		m_Movement = glm::vec3();
	}
}
