#pragma once
#include "Component.h"
#include <string>
#include <chrono>
#include "TextComponent.h"
#include <memory>

namespace dae
{
	class FPSComponent : public Component
	{
	public:
		FPSComponent(GameObject* pObject);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

	private:
		TextComponent* m_pTextComponent;
	};
}