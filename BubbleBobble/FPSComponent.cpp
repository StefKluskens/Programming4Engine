#include "FPSComponent.h"
#include <iostream>
#include "GameObject.h"
#include "TextComponent.h"

Game::FPSComponent::FPSComponent(dae::GameObject* pObject)
	: Component(pObject)
	, m_pTextComponent(pObject->GetComponent<dae::TextComponent>())
{
}

Game::FPSComponent::FPSComponent(FPSComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pTextComponent = std::move(other.m_pTextComponent);
}

void Game::FPSComponent::Render() const
{
}

void Game::FPSComponent::Update(float deltaTime)
{
	if (m_pTextComponent != nullptr)
	{
		std::string fps = std::to_string(int(1 / deltaTime)) + " fps";
		m_pTextComponent->SetText(fps);
	}
}