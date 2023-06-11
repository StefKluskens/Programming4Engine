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
	object->SetMarkForDelete(true);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	m_pRoot->Update(deltaTime);

	//Delete collider
	for (auto it = m_pColliders.begin(); it != m_pColliders.end();)
	{
		if ((*it)->GetOwner()->GetMarkForDelete())
		{
			it = m_pColliders.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	//Delete object
	for (auto it = m_pRoot->m_pChildren.begin(); it != m_pRoot->m_pChildren.end();)
	{
		if ((*it)->GetMarkForDelete())
		{
			it = m_pRoot->m_pChildren.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void dae::Scene::FixedUpdate(float deltaTime)
{
	m_pRoot->FixedUpdate(deltaTime);
}

void Scene::Render() const
{
	m_pRoot->Render();
}

void dae::Scene::OnSceneExit()
{

}

