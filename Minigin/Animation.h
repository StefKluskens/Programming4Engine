#pragma once
#include <string>

namespace dae
{
	struct Animation
	{
		Animation(std::string name, int frameWidth, int frameHeight, int nrOfFrames, float frameTime)
		{
			Name = name;
			FrameWidth = frameWidth;
			FrameHeight = frameHeight;
			NumberOfFrames = nrOfFrames;
			FrameTime = frameTime;
		}

		Animation(Animation anim)
		{
			Name = anim.Name;
			FrameWidth = anim.FrameWidth;
			FrameHeight = anim.FrameHeight;
			NumberOfFrames = anim.NumberOfFrames;
			FrameTime = anim.FrameTime;
		}

		std::string Name{};
		int FrameWidth{};
		int FrameHeight{};
		int NumberOfFrames{};
		float FrameTime{};
	};
}