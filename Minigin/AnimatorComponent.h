#pragma once
#include "Component.h"
#include "Animation.h"
#include <SDL_rect.h>
#include <vector>

namespace dae
{
	class AnimatorComponent : public Component
	{
	public:
		AnimatorComponent(GameObject* pObject, TextureComponent* pTexture);
		virtual ~AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) noexcept;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;

		void Render() const override {};
		void Update(float deltaTime) override;
		void FixedUpdate(float /*deltaTime*/) override {};

		Animation* CreateAnimation(std::string animName, TextureComponent* pTexture, int frameWidth, int frameHeight, int numFrames, float frameTime);
		void SetAnimation(Animation* pAnimation);

		SDL_Rect GetSrcRect() const { return m_SrcRect; }

		void DeleteAnimation();

		bool IsAnimationFinished() const { return m_IsAnimationFinished; }
		void ResetAnimationFinished() { m_IsAnimationFinished = false; }

	private:
		TextureComponent* m_pSpriteSheet{};
		Animation* m_pCurrentAnimation{};
		int m_CurrentFrame;
		float m_Timer;
		SDL_Rect m_SrcRect;
		SDL_Rect m_DestRect;

		bool m_IsAnimationFinished{false};
	};
}