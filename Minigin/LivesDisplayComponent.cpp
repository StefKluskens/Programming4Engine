#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "LivesComponent.h"

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* pObject, LivesComponent* pLivesComponent)
	: Component (pObject)
	, m_pTextComponent(pObject->GetComponent<TextComponent>())
	, m_pLivesComponent(pLivesComponent)
{
	std::string text = std::to_string(m_pLivesComponent->GetLives()) + " lives";
	m_pTextComponent->SetText(text);
}

dae::LivesDisplayComponent::LivesDisplayComponent(LivesDisplayComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pTextComponent = std::move(other.m_pTextComponent);
	m_pLivesComponent = std::move(other.m_pLivesComponent);
}

void dae::LivesDisplayComponent::Render() const
{
}

void dae::LivesDisplayComponent::Update([[maybe_unused]] float deltaTime)
{
}

void dae::LivesDisplayComponent::Notify(Event event)
{
	switch (event)
	{
	case dae::Event::PlayerDied:
	{
		std::string text = std::to_string(m_pLivesComponent->GetLives()) + " lives";
		m_pTextComponent->SetText(text);
		break;
	}		
	default:
		break;
	}
}
