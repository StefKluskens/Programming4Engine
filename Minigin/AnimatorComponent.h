#pragma once
#include "Component.h"
#include <SDL_rect.h>

namespace dae
{
	class TextureComponent;

	class AnimatorComponent : public Component
	{
	public:
		AnimatorComponent(dae::GameObject* pObject, TextureComponent* pTexture, int frameWidth, int frameHeight, int numFrames, float frameTime);
		virtual ~AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) noexcept = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float /*deltaTime*/) override {};

	private:
		TextureComponent* m_pSpriteSheet;
		int m_FrameWidth;
		int m_FrameHeight;
		int m_NumFrames;
		float m_FrameTime;
		int m_CurrentFrame;
		float m_Timer;
		SDL_Rect m_SrcRect;
		SDL_Rect m_DestRect;
	};
}