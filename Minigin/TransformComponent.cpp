#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pGameObject)
	: Component(pGameObject)
{
	m_pParent = pGameObject->GetParent();
}

void dae::TransformComponent::Render() const
{
}

void dae::TransformComponent::Update([[maybe_unused]]float deltaTime)
{
}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return m_LocalPos;
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_LocalPos.x = x;
	m_LocalPos.y = y;
	m_LocalPos.z = z;

	SetPositionDirty();
}

void dae::TransformComponent::SetPosition(glm::vec3 pos)
{
	m_LocalPos = pos;

	SetPositionDirty();
}

void dae::TransformComponent::AddPosition(glm::vec3 pos)
{
	m_LocalPos += pos;

	SetPositionDirty();
}

const float dae::TransformComponent::GetRotation()
{
	return m_Rotation;
}

void dae::TransformComponent::SetRotation(float angle)
{
	m_Rotation = angle;

	SetPositionDirty();
}

void dae::TransformComponent::AddRotation(float rot)
{
	m_Rotation += rot;

	SetPositionDirty();
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos = pos;
	
	SetPositionDirty();
}

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_IsPosDirty)
	{
		UpdateWorldPosition();
	}

	return m_WorldPos;
}

void dae::TransformComponent::SetPositionDirty()
{
	m_IsPosDirty = true;

	auto children = GetGameObject()->GetChildren();
	for (auto child : children)
	{
		child->GetTransform()->SetPositionDirty();
	}
}

void dae::TransformComponent::UpdateWorldPosition()
{
	if (m_IsPosDirty)
	{
		if (m_pParent == nullptr)
		{
			m_WorldPos = m_LocalPos;
		}
		else
		{
			auto parentPos = m_pParent->GetComponent<TransformComponent>()->GetWorldPosition();
			m_WorldPos = parentPos + m_LocalPos;
		}
	}

	m_IsPosDirty = false;
}