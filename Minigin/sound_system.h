#pragma once

namespace dae
{
	using sound_id = unsigned short;
	class sound_system
	{
	public:
		virtual ~sound_system() = default;
		virtual void Play(const sound_id id, const float volume) = 0;
	};
}