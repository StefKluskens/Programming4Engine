#pragma once
#include <memory>
#include "sound_system.h"
namespace dae
{
	class NullSoundSystem final : public sound_system
	{
		NullSoundSystem() = default;
		virtual ~NullSoundSystem() = default;

		virtual void Play(const int /*soundId*/, const float /*volume*/) override {};
		virtual void Update() override {};
		virtual void AddSound(const std::string& /*soundName*/) override {};
	};

	class ServiceLocator final
	{
	public:
		static sound_system& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<sound_system>&& ss) { _ss_instance = std::move(ss); }

	private:
		static std::unique_ptr<sound_system> _ss_instance;
	};
}