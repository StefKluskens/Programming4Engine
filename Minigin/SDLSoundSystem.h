#pragma once
#include "sound_system.h"
#include <memory>

namespace dae
{
	class SDLSoundSystem final : public sound_system
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		virtual void Play(const int soundId, const float volume) override;
		virtual void Update() override;
		virtual void AddSound(const std::string& soundName) override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}