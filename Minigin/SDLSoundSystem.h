#pragma once
#include "sound_system.h"

namespace dae
{
	class SDLSoundSystem final : public sound_system
	{
	public:
		SDLSoundSystem() = default;
		virtual ~SDLSoundSystem() = default;
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;


		virtual void Play(const sound_id id, const float volume) override;
	};
}