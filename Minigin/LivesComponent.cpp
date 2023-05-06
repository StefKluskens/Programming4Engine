#include "LivesComponent.h"
#include "LivesDisplayComponent.h"
#include "Subject.h"

Game::LivesComponent::LivesComponent(dae::GameObject* pObject, int lives)
	: Component(pObject)
	, m_Lives(lives)
{
	m_pLivesSubject = std::make_unique<dae::Subject>();
}

Game::LivesComponent::LivesComponent(LivesComponent&& other) noexcept
	: Component(std::move(other))
{
	m_Lives = std::move(other.m_Lives);
	m_pLivesSubject = std::move(other.m_pLivesSubject);
}

void Game::LivesComponent::AddObserver(dae::Observer* pObserver)
{
	m_pLivesSubject->AddObserver(pObserver);
}

void Game::LivesComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pLivesSubject->RemoveObserver(pObserver);
}

void Game::LivesComponent::Die()
{
	if (m_Lives <= 0)
	{
		return;
	}
	--m_Lives;

	//Notify LivesDisplay to update text
	m_pLivesSubject->Notify(dae::Event::PlayerDied);
}
