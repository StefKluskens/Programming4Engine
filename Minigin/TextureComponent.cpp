#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pGameObject)
	: Component(pGameObject)
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}

void dae::TextureComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		if (m_pTransform)
		{
			auto pos = m_pTransform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}
}

void dae::TextureComponent::Update([[maybe_unused]] float deltaTime)
{
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
