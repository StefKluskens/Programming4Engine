#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
}

namespace Game
{
	class ScoreComponent;

	class ScoreDisplay : public dae::Component, public dae::Observer
	{
	public:
		ScoreDisplay(dae::GameObject* pObject, ScoreComponent* pScoreComponent);
		virtual ~ScoreDisplay() = default;
		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) noexcept = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate([[maybe_unused]] float deltaTime) override {};

		void Notify(dae::Event event) override;

	private:
		ScoreComponent* m_pScoreComponent;
		dae::TextComponent* m_pTextComponent;
	};
}