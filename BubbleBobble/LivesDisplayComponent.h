#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
}

namespace Game
{
	class LivesComponent;

	class LivesDisplayComponent : public dae::Component, public dae::Observer
	{
	public:
		LivesDisplayComponent(dae::GameObject* pObject, LivesComponent* pLivesComponent);
		virtual ~LivesDisplayComponent() = default;
		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) noexcept = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate([[maybe_unused]] float deltaTime) override {};

		void Notify(dae::Event event) override;

	private:
		dae::TextComponent* m_pTextComponent;
		LivesComponent* m_pLivesComponent;
	};
}