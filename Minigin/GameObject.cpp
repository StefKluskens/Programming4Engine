#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update([[maybe_unused]] float deltaTime)
{ 
	for (const auto component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const auto component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_pComponents.emplace_back(component);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_transform;
}
