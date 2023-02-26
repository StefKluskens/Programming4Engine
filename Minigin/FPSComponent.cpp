#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(TextComponent& TextComponent)
	: m_StartPoint(std::chrono::high_resolution_clock::now())
	, m_pTextComponent(TextComponent)
{
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::Update([[maybe_unused]] float deltaTime)
{
	auto endTime = std::chrono::high_resolution_clock::now();

	double frameTime = std::chrono::duration<double>(endTime - m_StartPoint).count();

	m_TotalTime += frameTime;

	++m_FrameCount;

	if (m_TotalTime >= 1.0)
	{
		//Calculate fps
		m_Fps = m_FrameCount / static_cast<int>(m_TotalTime);

		m_pTextComponent.SetText(std::to_string(m_Fps) + " FPS");

		//Reset variables
		m_FrameCount = 0;
		m_TotalTime = 0.0;

		//Reset timer
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}
}

std::string dae::FPSComponent::GetFPS() const
{
	std::string text = std::to_string(m_Fps) + " FPS";
	return text;
}
