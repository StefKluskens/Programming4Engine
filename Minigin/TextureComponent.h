#pragma once
#include "Component.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "SDL_rect.h"
#include "SDL_render.h"

namespace dae
{
	class Texture2D;
	class Transform;

	class TextureComponent : public Component
	{
	public:
		TextureComponent(GameObject* pObject);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};

		void SetTexture(const std::string& filename);

		Texture2D* GetTexture() const;

		bool IsTextureSet();

		glm::vec2 GetSize() const;

		void SetIsAnimation(bool isAnim);

		void SetTextureVisibility(bool isVisible);

		void SetSourceRect(SDL_Rect srcRect);

		SDL_RendererFlip GetFlip() const { return m_Flip; }
		void SetFlip(SDL_RendererFlip flip) { m_Flip = flip; }

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		glm::vec3 m_Position{};
		Transform* m_pTransform{};

		bool m_IsAnimation{};
		bool m_IsVisible{};

		SDL_Rect m_SrcRect{};
		SDL_RendererFlip m_Flip{ SDL_FLIP_NONE };
	};
}