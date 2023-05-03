#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class ScoreComponent;
	class TextComponent;

	class ScoreDisplay : public Component, public Observer
	{
	public:
		ScoreDisplay(GameObject* pObject, ScoreComponent* pScoreComponent);
		virtual ~ScoreDisplay() = default;
		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) noexcept = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		void Notify(Event event) override;

	private:
		ScoreComponent* m_pScoreComponent;
		TextComponent* m_pTextComponent;
	};
}