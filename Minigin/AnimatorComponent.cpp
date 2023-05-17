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

void dae::AnimatorComponent::Update(float deltaTime)
{
	m_Timer += deltaTime;

	if (m_Timer >= m_pCurrentAnimation->FrameTime)
	{
		m_Timer -= m_pCurrentAnimation->FrameTime;
		m_CurrentFrame = (m_CurrentFrame + 1) % m_pCurrentAnimation->NumberOfFrames;
		m_SrcRect.x = m_CurrentFrame * m_pCurrentAnimation->FrameWidth;
	}

	m_pSpriteSheet->SetSourceRect(m_SrcRect);
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
