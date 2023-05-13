#pragma once
#include <string>

namespace dae
{
	class sound_system
	{
	public:
		virtual ~sound_system() = default;
		virtual void Update() = 0;
		virtual void Play(const int soundId, const float volume) = 0;
		virtual void AddSound(const std::string& soundName) = 0;
	};
}