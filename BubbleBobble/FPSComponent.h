#pragma once
#include "Component.h"
#include <string>
#include <chrono>
#include <memory>

namespace dae
{
	class TextComponent;
}

namespace Game
{
	class FPSComponent : public dae::Component
	{
	public:
		FPSComponent(dae::GameObject* pObject);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float /*deltaTime*/) override {};

	private:
		dae::TextComponent* m_pTextComponent;
	};
}