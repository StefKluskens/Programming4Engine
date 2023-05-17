#pragma once
#include "Component.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "SDL_rect.h"

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
		//void SetPosition(float x, float y);

		Texture2D* GetTexture() const;

		bool IsTextureSet();

		glm::vec2 GetSize() const;

		void SetIsAnimation(bool isAnim);

		void SetTextureVisibility(bool isVisible);

		void SetSourceRect(SDL_Rect srcRect);

	private:
		//TODO: Check if this could this be a unique_ptr
		std::shared_ptr<Texture2D> m_pTexture{};
		glm::vec3 m_Position{};
		Transform* m_pTransform{};

		bool m_IsAnimation{};
		bool m_IsVisible{};

		SDL_Rect m_SrcRect{};
	};
}