#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "XBoxController.h"

using namespace dae;

class XBoxController::XBoxControllerImpl final
{
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonPressedThisFrame;
	WORD m_ButtonReleasedThisFrame;

	int m_ControllerIndex;

	float m_LeftStickX;
	float m_LeftStickY;

public:
	XBoxControllerImpl(int controllerIndex)
		: m_ControllerIndex(controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		m_LeftStickX = m_CurrentState.Gamepad.sThumbLX;
		m_LeftStickY = m_CurrentState.Gamepad.sThumbLY;
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonPressedThisFrame & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonReleasedThisFrame & button;
	}

	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	float GetLeftJoystickXDirection() const
	{
		return m_LeftStickX;
	}

	float GetLeftJoystickYDirection() const
	{
		return m_LeftStickY;
	}
};

XBoxController::XBoxController(int controllerIndex)
{
	m_pImpl = std::make_unique<XBoxControllerImpl>(controllerIndex);
}

XBoxController::~XBoxController()
{
}

void XBoxController::Update()
{
	m_pImpl->Update();
}

bool XBoxController::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool XBoxController::IsUp(ControllerButton button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool XBoxController::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

float dae::XBoxController::GetLeftJoystickXDirection() const
{
	return m_pImpl->GetLeftJoystickXDirection();
}

float dae::XBoxController::GetLeftJoystickYDirection() const
{
	return m_pImpl->GetLeftJoystickYDirection();
}
