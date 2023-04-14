#include "FPSComponent.h"
#include <iostream>
#include "GameObject.h"

dae::FPSComponent::FPSComponent(GameObject* pObject)
	: Component(pObject)
	, m_pTextComponent(pObject->GetComponent<TextComponent>())
{
}

dae::FPSComponent::FPSComponent(FPSComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pTextComponent = std::move(other.m_pTextComponent);
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	if (m_pTextComponent != nullptr)
	{
		std::string fps = std::to_string(int(1 / deltaTime)) + " fps";
		m_pTextComponent->SetText(fps);
	}
}