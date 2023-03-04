#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include <iostream>

namespace dae
{
	class Component;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(std::shared_ptr<Component> component);
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

		Transform GetTransform() const;

		void SetParent(GameObject* pParent);
		void AddChild(GameObject* pGameObject);
		void RemoveChild(GameObject* pGameObject);

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};

		//TODO: Unique ptr?
		std::vector<std::shared_ptr<Component>> m_pComponents{};

		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};
	};

	template<typename T>
	inline T* dae::GameObject::GetComponent() const
	{
		T* temp{};

		for (size_t i = 0; i < m_pComponents.size(); ++i)
		{
			temp = dynamic_cast<T*>(m_pComponents[i].get());
			if (temp)
				return temp;
		}
		return nullptr;
	}

	//TODO: Will remove the first component of the matching type, find a fix for this, maybe give the components a name and search for the name instead of the type
	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		//m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), GetComponent<T>()), m_pComponents.end());
		for (auto it{ m_pComponents.begin() }; it != m_pComponents.end(); ++it)
		{
			if (dynamic_cast<T*>(it->get()))
			{
				m_pComponents.erase(it);
				break;
			}
		}
	}
}