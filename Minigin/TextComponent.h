#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include "Transform.h"

namespace dae 
{
	class Font;
	class Texture2D;

	class TextComponent : public Component
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		std::string GetText() const;
		std::shared_ptr<Font> GetFont() const;

	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}