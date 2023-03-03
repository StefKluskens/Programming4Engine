#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<TextComponent> TextComponent)
	: m_pTextComponent(TextComponent)
{
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	if (m_pTextComponent != nullptr)
	{
		std::string fps = std::to_string(int(1 / deltaTime)) + "fps";
		m_pTextComponent->SetText(fps);
	}		
}