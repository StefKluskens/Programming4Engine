#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include "SDL.h"
#include <queue>
#include <thread>
#include <condition_variable>
#include <map>
#include <unordered_map>

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
public:
	SDLSoundSystemImpl()
	{
		SDL_Init(SDL_INIT_AUDIO);

		Mix_Init(MIX_INIT_OGG);

		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

		m_Thread = std::jthread(&SDLSoundSystemImpl::Update, this);
	}

	~SDLSoundSystemImpl()
	{
		m_StopUpdateThread = true;
		m_Condition.notify_one();

		m_Thread.join();

		ClearQueue();
		ClearSounds();

		Mix_CloseAudio();
		Mix_CloseAudio();

		SDL_QuitSubSystem(SDL_INIT_AUDIO);
	}

	void Play(const int soundId, const float volume)
	{
		std::lock_guard<std::mutex> lock(m_QueueMutex);
		Sound sound;
		sound.SoundId = soundId;
		sound.Volume = volume;
		m_SoundsQueue.push(sound);
		m_Condition.notify_one();
	}

	void Update()
	{
		while (!m_StopUpdateThread)
		{
			std::unique_lock<std::mutex> lock(m_QueueMutex);
			m_Condition.wait(lock, [this] {return !m_SoundsQueue.empty() || m_StopUpdateThread; });

			if (m_StopUpdateThread)
			{
				break;
			}

			/*while (!m_SoundsQueue.empty())
			{
				const Sound& sound = m_SoundsQueue.front();
				PlaySound(sound.SoundId, sound.Volume);
				m_SoundsQueue.pop();
			}*/
			//lock.unlock();
			
			const Sound& sound = m_SoundsQueue.front();
			m_SoundsQueue.pop();
			lock.unlock();

			PlaySound(sound.SoundId, sound.Volume);			
			
		}
	}

	void AddSound(const std::string& soundName)
	{
		Mix_Chunk* soundEffect = Mix_LoadWAV(soundName.c_str());
		if (soundEffect != nullptr)
		{
			std::lock_guard<std::mutex> lock(m_SoundMutex);
			m_SoundEffects.push_back(soundEffect);
		}
	}

private:
	void PlaySound(int id, float volume)
	{
		std::lock_guard<std::mutex> lock(m_SoundMutex);
		if (id >= 0 && id < static_cast<int>(m_SoundEffects.size()))
		{
			Mix_Chunk* soundEffect = m_SoundEffects[id];
			if (soundEffect)
			{
				int channel = Mix_PlayChannel(-1, soundEffect, 0);
				if (channel != -1)
				{
					Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
				}
			}
		}
	}

	void ClearQueue()
	{
		std::lock_guard<std::mutex> lock(m_QueueMutex);
		while (!m_SoundsQueue.empty())
		{
			m_SoundsQueue.pop();
		}
	}

	void ClearSounds()
	{
		std::lock_guard<std::mutex> lock(m_SoundMutex);
		for (Mix_Chunk* soundEffect : m_SoundEffects)
		{
			Mix_FreeChunk(soundEffect);
		}
		m_SoundEffects.clear();
	}

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

dae::SDLSoundSystem::SDLSoundSystem()
	: m_pImpl(std::make_unique<SDLSoundSystemImpl>())
{
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
}

void dae::SDLSoundSystem::Play(const int soundId, const float volume)
{
	m_pImpl->Play(soundId, volume);
}

void dae::SDLSoundSystem::Update()
{
	m_pImpl->Update();
}

void dae::SDLSoundSystem::AddSound(const std::string& soundName)
{
	m_pImpl->AddSound(soundName);
}