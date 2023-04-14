#pragma once
#include "Component.h"

namespace dae 
{
	class GameObject;

	class RotatorComponent : public Component
	{
	public:
		RotatorComponent(GameObject* pObject, float radius, float rotSpeedRad);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) noexcept;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		virtual void Render() const override;
		virtual void Update(float deltaTime) override;
	private:
		float m_Radius{};
		float m_RotSpeed{};
		float m_CurrentRadians{};
		glm::vec3 m_Center{};

		GameObject* m_pOwner{};
	};
}