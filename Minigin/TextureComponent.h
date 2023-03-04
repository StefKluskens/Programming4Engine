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
		TextureComponent(GameObject* pGameObject);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		void SetTexture(const std::string& filename);

	private:
		//TODO: Check if this could this be a unique_ptr
		std::shared_ptr<Texture2D> m_pTexture{};

		TransformComponent* m_pTransform{};
	};
}