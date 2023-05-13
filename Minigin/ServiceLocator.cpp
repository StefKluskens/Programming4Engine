#include "ServiceLocator.h"

std::unique_ptr<dae::sound_system> dae::ServiceLocator::_ss_instance{};

dae::sound_system& dae::ServiceLocator::GetSoundSystem()
{
	return *_ss_instance.get();
}
