#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Component.h"
#include <iostream>

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(Component* component);
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};

		std::vector<Component*> m_pComponents{};
	};

	template<typename T>
	inline T* dae::GameObject::GetComponent() const
	{
		T* temp{};

		for (size_t i = 0; i < m_pComponents.size(); ++i)
		{
			temp = dynamic_cast<T*>(m_pComponents[i]);
			if (temp)
				return temp;
		}
		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), GetComponent<T>()), m_pComponents.end());
	}
}
