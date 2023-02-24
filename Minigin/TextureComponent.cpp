#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent()
{
}

void dae::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_Position.x, m_Position.y);
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
