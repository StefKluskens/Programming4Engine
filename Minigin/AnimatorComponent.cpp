#include "AnimatorComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include <SDL.h>

dae::AnimatorComponent::AnimatorComponent(dae::GameObject* pObject, TextureComponent* pTexture)
	: Component(pObject)
	, m_pSpriteSheet(pTexture)
	, m_CurrentFrame(0)
	, m_Timer(0.0f)
{
	if (!m_pSpriteSheet)
	{
		std::cout << "No sprite sheet\n";
	}
}

void dae::AnimatorComponent::Render() const
{
	if (m_pSpriteSheet)
	{
		const glm::vec2& position = GetOwner()->GetTransform()->GetLocalPosition();
		const float width = static_cast<float>(m_pCurrentAnimation->FrameWidth);
		const float height = static_cast<float>(m_pCurrentAnimation->FrameHeight);

		// Calculate the source rectangle for the current frame
		SDL_Rect srcRect;
		srcRect.x = m_CurrentFrame * m_pCurrentAnimation->FrameWidth;
		srcRect.y = 0;  // Assuming the frames are stacked horizontally
		srcRect.w = m_pCurrentAnimation->FrameWidth;
		srcRect.h = m_pCurrentAnimation->FrameHeight;

		Renderer::GetInstance().RenderTexture(*m_pSpriteSheet->GetTexture(), position.x, position.y, width, height, srcRect);
	}
}

void dae::AnimatorComponent::Update(float deltaTime)
{
	m_Timer += deltaTime;

	if (m_Timer >= m_pCurrentAnimation->FrameTime)
	{
		m_Timer -= m_pCurrentAnimation->FrameTime;
		m_CurrentFrame = (m_CurrentFrame + 1) % m_pCurrentAnimation->NumberOfFrames;
		m_SrcRect.x = m_CurrentFrame * m_pCurrentAnimation->FrameWidth;
	}
}

dae::Animation* dae::AnimatorComponent::CreateAnimation(std::string animName, int frameWidth, int frameHeight, int numFrames, float frameTime)
{
	Animation* anim = new Animation(animName, frameWidth, frameHeight, numFrames, frameTime);
	return anim;
}

void dae::AnimatorComponent::SetAnimation(Animation* pAnimation)
{
	m_pCurrentAnimation = pAnimation;

	m_SrcRect = { 0, 0, pAnimation->FrameWidth, pAnimation->FrameHeight };
	m_DestRect = { 0, 0, pAnimation->FrameWidth, pAnimation->FrameHeight };
}
