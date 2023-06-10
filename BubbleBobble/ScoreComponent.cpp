#include "ScoreComponent.h"
#include "Subject.h"

Game::ScoreComponent::ScoreComponent(dae::GameObject* pObject)
	: Component(pObject)
	, m_Score(0)
{
	m_pScoreSubject = std::make_unique<dae::Subject>();
}

Game::ScoreComponent::ScoreComponent(ScoreComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pScoreSubject = std::move(other.m_pScoreSubject);
	m_Score = std::move(other.m_Score);
}

void Game::ScoreComponent::AddObserver(dae::Observer* pObserver)
{
	m_pScoreSubject->AddObserver(pObserver);
}

void Game::ScoreComponent::RemoveObserver(dae::Observer* pObserver)
{
	m_pScoreSubject->RemoveObserver(pObserver);
}

void Game::ScoreComponent::AddScore(int score)
{
	m_Score += score;

	m_pScoreSubject->Notify(dae::Event::Scored);
}
