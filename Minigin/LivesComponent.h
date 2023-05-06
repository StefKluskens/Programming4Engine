#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class LivesDisplayComponent;

	class LivesComponent : public Component
	{
	public:
		LivesComponent(GameObject* pObject, int lives);
		virtual ~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		void Render() const override {};
		void Update([[maybe_unused]]float deltaTime) override {};
		void FixedUpdate([[maybe_unused]] float deltaTime) override {};

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

		int GetLives() const { return m_Lives; };

		void Die();

	private:
		int m_Lives;

		std::unique_ptr<Subject> m_pLivesSubject;
	};
}


