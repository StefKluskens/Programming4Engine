#pragma once
#include <string>
#include "TextureComponent.h"

namespace dae
{
	struct Animation
	{
		Animation(std::string name, TextureComponent* pTexture, int frameWidth, int frameHeight, int nrOfFrames, float frameTime)
			: Name(name)
			, Texture(pTexture)
			, FrameWidth(frameWidth)
			, FrameHeight(frameHeight)
			, NumberOfFrames(nrOfFrames)
			, FrameTime(frameTime)
		{
		}

		Animation(const dae::Animation& anim)
		{
			Name = anim.Name;
			Texture = anim.Texture;
			FrameWidth = anim.FrameWidth;
			FrameHeight = anim.FrameHeight;
			NumberOfFrames = anim.NumberOfFrames;
			FrameTime = anim.FrameTime;
		}

		std::string Name{};
		TextureComponent* Texture{};
		int FrameWidth{};
		int FrameHeight{};
		int NumberOfFrames{};
		float FrameTime{};
	};
}