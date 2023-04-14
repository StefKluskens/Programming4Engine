#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pObject)
	: Component(pObject)
	, m_Score(0)
{
	m_pScoreSubject = std::make_unique<Subject>();
}

dae::ScoreComponent::ScoreComponent(ScoreComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pScoreSubject = std::move(other.m_pScoreSubject);
	m_Score = std::move(other.m_Score);
}

void dae::ScoreComponent::AddObserver(Observer* pObserver)
{
	m_pScoreSubject->AddObserver(pObserver);
}

void dae::ScoreComponent::AddScore(int score)
{
	m_Score += score;

	m_pScoreSubject->Notify(Event::PickUpFound);
}
