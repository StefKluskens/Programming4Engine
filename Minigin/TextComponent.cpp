#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

dae::TextComponent::TextComponent(GameObject* pObject, const std::string& text, std::shared_ptr<Font> font)
	: Component(pObject)
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(std::move(font))
	, m_TextTexture(nullptr)
{
	m_Transform = GetOwner()->GetTransform();
}

dae::TextComponent::TextComponent(TextComponent&& other) noexcept
	: Component(std::move(other))
{
	m_Text = std::move(other.m_Text);
	m_Transform = std::move(other.m_Transform);
	m_Font = std::move(other.m_Font);
	m_TextTexture = std::move(other.m_TextTexture);
	m_NeedsUpdate = std::move(other.m_NeedsUpdate);
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_Transform->GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::Update([[maybe_unused]] float deltaTime)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_Transform->SetLocalPosition(glm::vec3{ x,y,0.0f });
}

std::string dae::TextComponent::GetText() const
{
	return m_Text;
}

std::shared_ptr<dae::Font> dae::TextComponent::GetFont() const
{
	return m_Font;
}
