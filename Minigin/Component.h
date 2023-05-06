#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pObject);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = default;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render() const = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0;
		GameObject* GetOwner() const { return m_pAttachedObject; };

	protected:

	private:
		GameObject* m_pAttachedObject;
	};
}