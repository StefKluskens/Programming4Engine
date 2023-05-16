#include "AnimatorComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include <SDL.h>

dae::AnimatorComponent::AnimatorComponent(dae::GameObject* pObject, TextureComponent* pTexture, int frameWidth, int frameHeight, int numFrames, float frameTime)
	: Component(pObject)
	, m_pSpriteSheet(pTexture)
	, m_FrameWidth(frameWidth)
	, m_FrameHeight(frameHeight)
	, m_NumFrames(numFrames)
	, m_FrameTime(frameTime)
	, m_CurrentFrame(0)
	, m_Timer(0.0f)
{
	if (!m_pSpriteSheet)
	{
		std::cout << "No sprite sheet\n";
	}

	m_SrcRect = { 0, 0, frameWidth, frameHeight };
	m_DestRect = { 0, 0, frameWidth, frameHeight };
}

void dae::AnimatorComponent::Render() const
{
	if (m_pSpriteSheet)
	{
		const glm::vec2& position = GetOwner()->GetTransform()->GetLocalPosition();
		const float width = static_cast<float>(m_FrameWidth);
		const float height = static_cast<float>(m_FrameHeight);

		// Calculate the source rectangle for the current frame
		SDL_Rect srcRect;
		srcRect.x = m_CurrentFrame * m_FrameWidth;
		srcRect.y = 0;  // Assuming the frames are stacked horizontally
		srcRect.w = m_FrameWidth;
		srcRect.h = m_FrameHeight;

		Renderer::GetInstance().RenderTexture(*m_pSpriteSheet->GetTexture(), position.x, position.y, width, height, srcRect);
	}
}

void dae::AnimatorComponent::Update(float deltaTime)
{
	m_Timer += deltaTime;

	if (m_Timer >= m_FrameTime)
	{
		m_Timer -= m_FrameTime;
		m_CurrentFrame = (m_CurrentFrame + 1) % m_NumFrames;
		m_SrcRect.x = m_CurrentFrame * m_FrameWidth;
	}
}
