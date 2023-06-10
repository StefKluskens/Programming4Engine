#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

std::vector<ColliderComponent*> dae::Scene::GetColliders() const
{
	return m_pColliders;
}

std::string dae::Scene::GetName() const
{
	return m_name;
}

Scene::Scene(const std::string& name)
	: m_name(name)
	, m_pRoot(std::make_unique<GameObject>("Root Object", this))
{
}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	//m_objects.emplace_back(std::move(object));

	object->SetParent(m_pRoot.get(), true);

	auto pCollider = object->GetComponent<ColliderComponent>();
	if (pCollider)
	{
		m_pColliders.push_back(pCollider);
	}
}

void Scene::Remove(GameObject* object)
{
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		[object](const std::unique_ptr<GameObject>& ptr) { return ptr.get() == object; }),
		m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	/*for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}*/

	m_pRoot->Update(deltaTime);
}

void dae::Scene::FixedUpdate(float deltaTime)
{
	m_pRoot->FixedUpdate(deltaTime);

	/*for (int i{}; i < m_pColliders.size(); ++i)
	{
		if (m_pColliders[i]->NeedsToCheckCollision())
		{
			m_pColliders[i]->CollisionCheck();
		}

		if (m_pColliders[i]->NeedsToCheckGroundCollision())
		{
			m_pColliders[i]->DoGroundCheck();
		}
	}*/
}

void Scene::Render() const
{
	/*for (const auto& object : m_objects)
	{
		object->Render();
	}*/

	m_pRoot->Render();
}

void dae::Scene::OnSceneExit()
{

}

