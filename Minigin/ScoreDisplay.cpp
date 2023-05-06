#include "ScoreDisplay.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

Game::ScoreDisplay::ScoreDisplay(dae::GameObject* pObject, ScoreComponent* pScoreComponent)
	: Component(pObject)
	, m_pScoreComponent(pScoreComponent)
{
	m_pTextComponent = pObject->GetComponent<dae::TextComponent>();

	std::string text = "Score: " + std::to_string(m_pScoreComponent->GetScore());
	m_pTextComponent->SetText(text);
}

void Game::ScoreDisplay::Render() const
{
}

void Game::ScoreDisplay::Update([[maybe_unused]] float deltaTime)
{
}

void Game::ScoreDisplay::Notify(dae::Event event)
{
	if (event == dae::Event::PickUpFound)
	{
		std::string text = "Score: " + std::to_string(m_pScoreComponent->GetScore());
		m_pTextComponent->SetText(text);
	}
}
