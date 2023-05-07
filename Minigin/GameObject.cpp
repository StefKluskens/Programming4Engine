#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>

using namespace dae;

dae::GameObject::GameObject(std::string name)
	: m_Name(name)
{
	m_Transform = std::make_unique<Transform>(this);
}

GameObject::~GameObject() = default;

GameObject::GameObject(GameObject&& other) noexcept
{
	m_Transform = std::move(other.m_Transform);
	m_pComponents = std::move(other.m_pComponents);
	m_pChildren = std::move(other.m_pChildren);
	m_Name = std::move(other.m_Name);
	m_pParent = std::move(other.m_pParent);
}

void GameObject::Update(float deltaTime)
{ 
	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}

	for (auto& child : m_pChildren)
	{
		child->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}

	for (auto& child : m_pChildren)
	{
		child->FixedUpdate(deltaTime);
	}
}

void GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}

	for (auto& child : m_pChildren)
	{
		child->Render();
	}
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform->SetLocalPosition(glm::vec3{ x,y,0.0f });
}

void dae::GameObject::SetPosition(glm::vec3 pos)
{
	m_Transform->SetLocalPosition(pos);
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
	m_pComponents.emplace_back(std::move(component));
}

Transform* GameObject::GetTransform() const
{
	return m_Transform.get();
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPos)
{
	if (pParent == nullptr)
	{
		m_Transform->SetLocalPosition(m_Transform->GetWorldPosition());
	}
	else
	{
		if (keepWorldPos)
		{
			auto parentTransform = pParent->GetTransform()->GetWorldPosition();
			m_Transform->SetLocalPosition(m_Transform->GetLocalPosition() + parentTransform);
		}

		m_Transform->SetPositionDirty();
	}

	std::unique_ptr<GameObject> child;

	if (m_pParent != nullptr)
	{
		for (auto it = m_pParent->m_pChildren.begin(); it != m_pParent->m_pChildren.end(); ++it)
		{
			if (it->get() == this)
			{
				child = std::move(*it);
				m_pParent->m_pChildren.erase(it);
				break;
			}
		}
	}

	m_pParent = pParent;

	if (m_pParent != nullptr)
	{
		if (child == nullptr)
		{
			child = std::unique_ptr<GameObject>(this);
		}
		m_pParent->m_pChildren.emplace_back(std::move(child));
	}
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

std::string dae::GameObject::GetName() const
{
	return m_Name;
}
