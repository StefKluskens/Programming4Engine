#include "SDLSoundSystem.h"
#include "SDL_mixer.h"
#include "SDL.h"

dae::SDLSoundSystem::SDLSoundSystem()
{
	SDL_Init(SDL_INIT_AUDIO);

	Mix_Init(MIX_INIT_OGG);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	m_Thread = std::jthread(&SDLSoundSystem::Update, this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
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

void dae::SDLSoundSystem::Play(const int soundId, const float volume)
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);
	Sound sound;
	sound.SoundId = soundId;
	sound.Volume = volume;
	m_SoundsQueue.push(sound);
	m_Condition.notify_one();
}

void dae::SDLSoundSystem::Update()
{
	while (!m_StopUpdateThread)
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);
		m_Condition.wait(lock, [this] {return !m_SoundsQueue.empty() || m_StopUpdateThread; });

		if (m_StopUpdateThread)
		{
			break;
		}

		while (!m_SoundsQueue.empty())
		{
			const Sound& sound = m_SoundsQueue.front();
			PlaySound(sound.SoundId, sound.Volume);
			m_SoundsQueue.pop();
		}

		lock.unlock();
	}
}

void dae::SDLSoundSystem::AddSound(const std::string& soundName)
{
	Mix_Chunk* soundEffect = Mix_LoadWAV(soundName.c_str());
	if (soundEffect != nullptr)
	{
		std::lock_guard<std::mutex> lock(m_SoundMutex);
		m_SoundEffects.push_back(soundEffect);
	}
}

void dae::SDLSoundSystem::PlaySound(int id, float volume)
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

void dae::SDLSoundSystem::ClearQueue()
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);
	while (!m_SoundsQueue.empty())
	{
		m_SoundsQueue.pop();
	}
}

void dae::SDLSoundSystem::ClearSounds()
{
	std::lock_guard<std::mutex> lock(m_SoundMutex);
	for (Mix_Chunk* soundEffect : m_SoundEffects)
	{
		Mix_FreeChunk(soundEffect);
	}
	m_SoundEffects.clear();
}
