#pragma once
#include "Component.h"
#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace dae
{
	class Texture2D;

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
		void Update(float deltaTime) override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		glm::vec2 GetSize() const;

	private:
		//TODO: Check if this could this be a unique_ptr
		std::shared_ptr<Texture2D> m_pTexture{};
		glm::vec3 m_Position{};
	};
}