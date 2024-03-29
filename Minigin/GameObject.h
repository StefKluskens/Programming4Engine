#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include <iostream>
#include "Component.h"


namespace dae
{
	class Texture2D;
	class Scene;

	class GameObject final
	{
	public:
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void SetPosition(float x, float y);
		void SetPosition(glm::vec3 pos);

		GameObject(std::string name, Scene* pScene);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(std::unique_ptr<Component> component);
		template <typename T> T* GetComponent() const;
		template <typename T> T* GetComponent(std::string tag) const;
		template <typename T> void RemoveComponent();

		Transform* GetTransform() const;

		void SetParent(GameObject* pParent, bool keepWorldPos);
		GameObject* GetParent() const;

		std::string GetName() const;
		void SetName(const std::string& name);

		void SetTag(const std::string& tag) { m_Tag = tag; }
		std::string GetTag() const { return m_Tag; }

		//unique_ptr because I want the game object to have ownership of its children, seems the most logical to me
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};
		GameObject* GetChildByName(const std::string& name);
		std::vector<GameObject*> GetChildrenByTag(const std::string& tag);

		Scene* GetScene() const;

		void SetMarkForDelete(bool marked) { m_MarkForDelete = marked; }
		bool GetMarkForDelete() const { return m_MarkForDelete; }

	private:
		std::string m_Name{ "GameObject" };
		std::string m_Tag{ "" };
		std::unique_ptr<Transform> m_Transform{};

		//unique_ptr because the gameobject should own its components. No need for shared ownership
		std::vector<std::unique_ptr<Component>> m_pComponents{};

		GameObject* m_pParent{ nullptr };

		Scene* m_pScene;

		bool m_MarkForDelete{ false };
	};

	template<typename T>
	inline T* dae::GameObject::GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		T* temp{};

		for (size_t i = 0; i < m_pComponents.size(); ++i)
		{
			temp = dynamic_cast<T*>(m_pComponents[i].get());
			if (temp)
				return temp;
		}
		return nullptr;
	}

	template<typename T>
	inline T* GameObject::GetComponent(std::string tag) const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		T* temp{};

		for (size_t i = 0; i < m_pComponents.size(); ++i)
		{
			temp = dynamic_cast<T*>(m_pComponents[i].get());
			if (temp && temp->GetTag() == tag)
			{
				return temp;
			}	
		}
		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		/*auto it = std::remove_if(m_pComponents.begin(), m_pComponents.end(), [](const std::unique_ptr<Component>& pComponent)
			{
				return dynamic_cast<T*>(pComponent.get()) != nullptr;
			});
		m_pComponents.erase(it, m_pComponents.end());*/

		m_pComponents.erase(
			std::remove_if(
				m_pComponents.begin(),
				m_pComponents.end(),
				[](const std::unique_ptr<Component>& pComponent)
				{
					return dynamic_cast<T*>(pComponent.get()) != nullptr;
				}
			),
			m_pComponents.end()
					);
	}
}
