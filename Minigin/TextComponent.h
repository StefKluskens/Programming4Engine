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
		TextComponent(GameObject* pObject, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float /*deltaTime*/) override {};

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		std::string GetText() const;
		std::shared_ptr<Font> GetFont() const;

	private:
		std::string m_Text;
		Transform* m_Transform{};
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
		bool m_NeedsUpdate;
	};
}