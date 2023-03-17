#pragma once
#include "Component.h"

namespace dae
{
	class TransformComponent;

	class Rotator : public Component
	{
	public:
		Rotator(GameObject* pGameObject);
		virtual ~Rotator() = default;
		Rotator(const Rotator& other) = delete;
		Rotator(Rotator&& other) = delete;
		Rotator& operator=(const Rotator& other) = delete;
		Rotator& operator=(Rotator&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		void SetRadiusSpeed(float radius, float speed);
		void SetCenterPoint(const glm::vec3& center);
		void ShouldRotateAroundParent(bool rotateAroundParent);

	private:
		TransformComponent* m_pTransform{};

		float m_Radius{};
		float m_Speed{};

		glm::vec3 m_CenterPoint{};

		bool m_RotateAroundParent{};
	};
}