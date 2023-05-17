#pragma once
#include "Component.h"
#include "Animation.h"
#include <SDL_rect.h>
#include <vector>

namespace dae
{
	class TextureComponent;

	class AnimatorComponent : public Component
	{
	public:
		AnimatorComponent(dae::GameObject* pObject, TextureComponent* pTexture);
		virtual ~AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) noexcept = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;

		void Render() const override;
		void Update(float deltaTime) override;
		void FixedUpdate(float /*deltaTime*/) override {};

		Animation* CreateAnimation(std::string animName, int frameWidth, int frameHeight, int numFrames, float frameTime);
		void SetAnimation(Animation* pAnimation);

	private:
		TextureComponent* m_pSpriteSheet{};
		Animation* m_pCurrentAnimation{};
		int m_CurrentFrame;
		float m_Timer;
		SDL_Rect m_SrcRect;
		SDL_Rect m_DestRect;
	};
}