#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject* pObject)
	: Component(pObject)
	, m_LocalPosition(glm::vec3{ 0.0f, 0.0f, 0.0f })
	//, m_WorldPosition(glm::vec3{ 0.0f, 0.0f, 0.0f })
{
	m_WorldPosition = GetWorldPosition();
}

dae::Transform::Transform(Transform&& other) noexcept
	: Component(std::move(other))
{
	m_LocalPosition = std::move(other.m_LocalPosition);
	m_WorldPosition = std::move(other.m_WorldPosition);
	m_MovementSpeed = std::move(other.m_MovementSpeed);
	m_PositionIsDirty = std::move(other.m_PositionIsDirty);
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		auto pOwner = GetOwner();
		if (pOwner == nullptr)
		{
			return;
		}
		auto parent{ pOwner->GetParent() };
		if (parent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			auto transform = parent->GetTransform();
			if (transform)
			{
				m_WorldPosition = transform->GetWorldPosition() + m_LocalPosition;
			}
		}
		m_PositionIsDirty = false;
	}
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::Transform::SetPositionDirty()
{
	m_PositionIsDirty = true;
}
