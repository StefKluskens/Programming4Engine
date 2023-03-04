#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(GameObject* pGameObject)
	: Component(pGameObject)
{
	m_pTextComponent = GetGameObject()->GetComponent<TextComponent>();
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