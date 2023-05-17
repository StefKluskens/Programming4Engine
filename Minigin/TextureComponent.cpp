#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

dae::TextureComponent::TextureComponent(GameObject* pObject)
	: Component(pObject)
	, m_IsVisible(true)
{
	m_pTransform = pObject->GetTransform();
}

dae::TextureComponent::TextureComponent(TextureComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pTexture = std::move(other.m_pTexture);
	m_Position = std::move(other.m_Position);
}

void dae::TextureComponent::Render() const
{
	if (m_IsVisible && m_pTexture)
	{
		if (!m_IsAnimation)
		{
			auto pos = GetOwner()->GetTransform()->GetLocalPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
		else
		{
			const glm::vec2& position = GetOwner()->GetTransform()->GetLocalPosition();
			const float width = static_cast<float>(m_SrcRect.w);
			const float height = static_cast<float>(m_SrcRect.h);

			Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y, width, height, m_SrcRect);
		}
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

glm::vec2 dae::TextureComponent::GetSize() const
{
	float x = static_cast<float>(m_pTexture->GetSize().x);
	float y = static_cast<float>(m_pTexture->GetSize().y);

	return glm::vec2(x, y);
}

dae::Texture2D* dae::TextureComponent::GetTexture() const
{
	return m_pTexture.get();
}

bool dae::TextureComponent::IsTextureSet()
{
	if (m_pTexture.get())
	{
		return true;
	}

	return false;
}

void dae::TextureComponent::SetIsAnimation(bool isAnim)
{
	m_IsAnimation = isAnim;
}

void dae::TextureComponent::SetTextureVisibility(bool isVisible)
{
	m_IsVisible = isVisible;
}

void dae::TextureComponent::SetSourceRect(SDL_Rect srcRect)
{
	m_SrcRect = srcRect;
}
