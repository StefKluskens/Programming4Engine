#pragma once
//Windows input includes (pimpl this away)
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <XInput.h>

#include "Singleton.h"

//Include xinput.lib!!!!!!!!!!
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float deltaTime);

	private:
		//XINPUT_STATE m_CurrentState;
	};

}
