#pragma once
#include <memory>
#include "sound_system.h"
namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<sound_system> _ss_instance;
	public:
		static sound_system& GetSoundSystem() { return *_ss_instance; }
		static void RegisterSoundSystem(std::unique_ptr<sound_system>&& ss) { _ss_instance = std::move(ss); }
	};
}