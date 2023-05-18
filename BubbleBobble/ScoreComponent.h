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
	class ScoreComponent : public dae::Component
	{
	public:
		ScoreComponent(dae::GameObject* pObject);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void Render() const override {};
		void Update(float /*deltaTime*/) override {};
		void FixedUpdate(float /*deltaTime*/) override {};

		void AddObserver(dae::Observer* pObserver);
		void RemoveObserver(dae::Observer* pObserver);

		void AddScore(int score);
		int GetScore() const { return m_Score; };

	private:
		std::unique_ptr<dae::Subject> m_pScoreSubject;
		int m_Score;
	};
}