#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class LivesComponent;

	class LivesDisplayComponent : public Component, public Observer
	{
	public:
		LivesDisplayComponent(GameObject* pObject, LivesComponent* pLivesComponent);
		virtual ~LivesDisplayComponent() = default;
		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) noexcept;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		void Notify(Event event) override;

	private:
		TextComponent* m_pTextComponent;
		LivesComponent* m_pLivesComponent;
	};
}