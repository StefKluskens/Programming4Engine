#include "LivesComponent.h"
#include "LivesDisplayComponent.h"

dae::LivesComponent::LivesComponent(GameObject* pObject, int lives)
	: Component(pObject)
	, m_Lives(lives)
{
	m_pLivesSubject = std::make_unique<Subject>();
}

dae::LivesComponent::LivesComponent(LivesComponent&& other) noexcept
	: Component(std::move(other))
{
	m_Lives = std::move(other.m_Lives);
	m_pLivesSubject = std::move(other.m_pLivesSubject);
}

void dae::LivesComponent::AddObserver(Observer* pObserver)
{
	m_pLivesSubject->AddObserver(pObserver);
}

void dae::LivesComponent::RemoveObserver(Observer* pObserver)
{
	m_pLivesSubject->RemoveObserver(pObserver);
}

void dae::LivesComponent::Die()
{
	if (m_Lives <= 0)
	{
		return;
	}
	--m_Lives;

	//Notify LivesDisplay to update text
	m_pLivesSubject->Notify(Event::PlayerDied);
}
