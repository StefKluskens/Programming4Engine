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
		FPSComponent(TextComponent& pTextComponent);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;

		std::string GetFPS() const;

	private:
		int m_FrameCount{};
		double m_TotalTime{};
		std::chrono::steady_clock::time_point m_StartPoint{};
		int m_Fps{};
		TextComponent& m_pTextComponent;
	};
}