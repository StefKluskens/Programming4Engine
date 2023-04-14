#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

dae::TextureComponent::TextureComponent(GameObject* pObject)
	: Component(pObject)
{
}

dae::TextureComponent::TextureComponent(TextureComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pTexture = std::move(other.m_pTexture);
	m_Position = std::move(other.m_Position);
}

void dae::TextureComponent::Render() const
{
	if (m_pTexture)
	{
		auto pos = GetOwner()->GetTransform()->GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextureComponent::Update([[maybe_unused]] float deltaTime)
{
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
