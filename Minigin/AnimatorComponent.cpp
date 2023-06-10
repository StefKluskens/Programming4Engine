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
}

dae::AnimatorComponent::AnimatorComponent(AnimatorComponent&& other) noexcept
	: Component(std::move(other))
{
	m_pSpriteSheet = std::move(other.m_pSpriteSheet);
	m_pCurrentAnimation = std::move(other.m_pCurrentAnimation);
	m_CurrentFrame = std::move(other.m_CurrentFrame);
	m_Timer = std::move(other.m_Timer);
	m_SrcRect = std::move(other.m_SrcRect);
	m_DestRect = std::move(other.m_DestRect);
}

void dae::AnimatorComponent::Update(float deltaTime)
{
	if (!m_pCurrentAnimation)
	{
		return;
	}

	m_Timer += deltaTime;

	if (m_Timer >= m_pCurrentAnimation->FrameTime)
	{
		m_Timer -= m_pCurrentAnimation->FrameTime;
		m_CurrentFrame = (m_CurrentFrame + 1) % m_pCurrentAnimation->NumberOfFrames;
		m_SrcRect.x = m_CurrentFrame * m_pCurrentAnimation->FrameWidth;

		if (m_CurrentFrame == m_pCurrentAnimation->NumberOfFrames - 1)
		{
			m_IsAnimationFinished = true;
		}
	}

	m_pCurrentAnimation->Texture->SetSourceRect(m_SrcRect);
}

dae::Animation* dae::AnimatorComponent::CreateAnimation(std::string animName, TextureComponent* pTexture, int frameWidth, int frameHeight, int numFrames, float frameTime)
{
	return new Animation(animName, pTexture, frameWidth, frameHeight, numFrames, frameTime);
}

void dae::AnimatorComponent::SetAnimation(Animation* pAnimation)
{
	if (m_pCurrentAnimation == pAnimation)
	{
		return;
	}

	if (m_pCurrentAnimation)
	{
		m_pCurrentAnimation->Texture->SetTextureVisibility(false);
	}

	m_pCurrentAnimation = pAnimation;

	m_SrcRect = { 0, 0, pAnimation->FrameWidth, pAnimation->FrameHeight };
	m_DestRect = { 0, 0, pAnimation->FrameWidth, pAnimation->FrameHeight };

	m_pCurrentAnimation->Texture->SetTextureVisibility(true);
}

void dae::AnimatorComponent::DeleteAnimation()
{
	delete m_pCurrentAnimation;
}
