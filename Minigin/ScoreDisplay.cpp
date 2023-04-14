#include "ScoreDisplay.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

dae::ScoreDisplay::ScoreDisplay(GameObject* pObject, ScoreComponent* pScoreComponent)
	: Component(pObject)
	, m_pScoreComponent(pScoreComponent)
{
	m_pTextComponent = pObject->GetComponent<TextComponent>();

	std::string text = "Score: " + std::to_string(m_pScoreComponent->GetScore());
	m_pTextComponent->SetText(text);
}

dae::ScoreDisplay::ScoreDisplay(ScoreDisplay&& other) noexcept
	: Component(std::move(other))
{
	m_pScoreComponent = std::move(other.m_pScoreComponent);
	m_pTextComponent = std::move(other.m_pTextComponent);
}

void dae::ScoreDisplay::Render() const
{
}

void dae::ScoreDisplay::Update([[maybe_unused]] float deltaTime)
{
}

void dae::ScoreDisplay::Notify(Event event)
{
	if (event == dae::Event::PickUpFound)
	{
		std::string text = "Score: " + std::to_string(m_pScoreComponent->GetScore());
		m_pTextComponent->SetText(text);
	}
}
