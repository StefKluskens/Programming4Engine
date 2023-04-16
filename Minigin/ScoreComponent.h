#pragma once
#include "Component.h"
#include "Subject.h"
//#pragma warning(push)
//#pragma warning(disable: 6340)
//#include "SteamAchievementsGlobals.h"
//#pragma warning(pop)

namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* pObject);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void Render() const override {};
		void Update([[maybe_unused]]float deltaTime) override {};

		void AddObserver(Observer* pObserver);

		void AddScore(int score);
		int GetScore() const { return m_Score; };

	private:
		std::unique_ptr<Subject> m_pScoreSubject;
		int m_Score;
	};
}