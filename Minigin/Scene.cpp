#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) 
	: m_name(name)
	, m_pRoot(std::make_unique<GameObject>("Root Object"))
{
}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	//m_objects.emplace_back(std::move(object));

	object->SetParent(m_pRoot.get(), true);
}

void Scene::Remove([[maybe_unused]]std::shared_ptr<GameObject> object)
{
	//m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
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

void Scene::Render() const
{
	/*for (const auto& object : m_objects)
	{
		object->Render();
	}*/

	m_pRoot->Render();
}

