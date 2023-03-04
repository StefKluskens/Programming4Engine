#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TransformComponent.h"

dae::TextComponent::TextComponent(GameObject* pGameObject)
	: Component(pGameObject)
	, m_needsUpdate(true)
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}

void dae::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		if (m_pTransform)
		{
			auto pos = m_pTransform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
	}
}

void dae::TextComponent::Update(float)
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
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
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_font = font;
}

std::string dae::TextComponent::GetText() const
{
	return m_text;
}

std::shared_ptr<dae::Font> dae::TextComponent::GetFont() const
{
	return m_font;
}
