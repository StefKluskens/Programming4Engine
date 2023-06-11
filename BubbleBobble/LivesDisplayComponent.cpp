#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "LivesComponent.h"

Game::LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* pObject, LivesComponent* pLivesComponent, dae::TextComponent* pTextComponent)
	: Component (pObject)
	, m_pTextComponent(pTextComponent)
	, m_pLivesComponent(pLivesComponent)
{
	std::string text = std::to_string(m_pLivesComponent->GetLives()) + " lives";
	m_pTextComponent->SetText(text);
}

void Game::LivesDisplayComponent::Render() const
{
}

void Game::LivesDisplayComponent::Update(float /*deltaTime*/)
{
}

void Game::LivesDisplayComponent::Notify(dae::Event event)
{
	switch (event)
	{
	case dae::Event::PlayerDied:
	{
		std::string text = std::to_string(m_pLivesComponent->GetLives()) + "lives";
		m_pTextComponent->SetText(text);
		break;
	}		
	default:
		break;
	}
}
