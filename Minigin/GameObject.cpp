#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>
#include "Component.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
{
	m_pTransform = std::make_shared<TransformComponent>(this);
	AddComponent(m_pTransform);
}

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
	m_pTransform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_pComponents.emplace_back(component);
}

dae::TransformComponent* dae::GameObject::GetTransform() const
{
	return m_pTransform.get();
}

void dae::GameObject::SetParent(GameObject* pParent)
{
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pParent;

	m_pParent->AddChild(this);
}

void dae::GameObject::AddChild(GameObject* pGameObject)
{
	m_pChildren.emplace_back(pGameObject);
}

void dae::GameObject::RemoveChild([[maybe_unused]] GameObject* pGameObject)
{
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), pGameObject), m_pChildren.end());
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

std::vector<dae::GameObject*> dae::GameObject::GetChildren() const
{
	return m_pChildren;
}
