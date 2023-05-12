#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class ColliderComponent;

	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::vector<ColliderComponent*> GetColliders() const;

		std::string GetName() const;


	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::unique_ptr<GameObject> m_pRoot;
		std::vector<std::unique_ptr<GameObject>> m_objects;
		std::vector<ColliderComponent*> m_pColliders;

		static unsigned int m_idCounter; 
	};

}
