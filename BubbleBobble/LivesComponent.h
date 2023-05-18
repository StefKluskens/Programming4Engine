#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class Subject;
	class Observer;
}

namespace Game
{
	class LivesDisplayComponent;

	class LivesComponent : public dae::Component
	{
	public:
		LivesComponent(dae::GameObject* pObject, int lives);
		virtual ~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};

		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);

		int GetLives() const { return m_Lives; };

		void Die();

	private:
		int m_Lives;

		std::unique_ptr<dae::Subject> m_pLivesSubject;
	};
}


