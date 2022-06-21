
#include "Controller.h"

Controller::Controller()
{
	
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &m_state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}
}

Controller::~Controller()
{
}

void Controller::Update()
{
	m_oldState = m_state.Gamepad;
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &m_state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}
}
