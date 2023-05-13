#pragma once
#include "sound_system.h"
#include <queue>
#include <memory>
#include <thread>
#include <condition_variable>
#include <map>
#include <unordered_map>

struct Mix_Chunk;

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
		void PlaySound(int id, float volume);
		void ClearQueue();
		void ClearSounds();

		struct Sound
		{
			int SoundId{};
			float Volume{};
		};

		std::vector<Mix_Chunk*> m_SoundEffects;
		std::jthread m_Thread;
		std::atomic<bool> m_StopUpdateThread{ false };
		std::queue<Sound> m_SoundsQueue{};
		std::mutex m_QueueMutex{};
		std::condition_variable m_Condition{};
		std::mutex m_SoundMutex{};
	};
}