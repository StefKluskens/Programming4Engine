#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>

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
	/*const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);*/

	for (const auto component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetTexture([[maybe_unused]] const std::string& filename)
{
	//m_texture = ResourceManager::GetInstance().LoadTexture(filename);
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
