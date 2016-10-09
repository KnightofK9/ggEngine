#include "Input.h"
#include "Debug.h"

namespace ggEngine
{
	Input::Input(HWND *hWnd)
	{
		HRESULT result = DirectInput8Create
		(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&dInput,
			NULL
		);
		if (FAILED(result))
			g_debug.Log("Error initialize Input");
		this->hWnd = hWnd;
		return;
	}

	Input::~Input()
	{
		if (diKeyboard != NULL)
		{
			diKeyboard->Unacquire();
			diKeyboard->Release();
			diKeyboard = NULL;
		}
		if (diMouse != NULL)
		{
			diMouse->Unacquire();
			diMouse->Release();
			diMouse = NULL;
		}
	}

#pragma region keyBoard
	int Input::InitKeyboard()
	{
		HRESULT result;
		result = dInput->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetCooperativeLevel((*hWnd), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diKeyboard->Acquire();
		if (FAILED(result))
			return 0;
		return 1;
	}

	int Input::KeyDown(int keyCode)
	{
		// Log
		int keyDown = keyStates[keyCode] & 0x80;
	/*	if (keyDown != 0)
			Debug::Log("Virtual key code: " + std::to_string(keyDown));*/
		//

		return keyStates[keyCode] & 0x80;
	}

	void Input::PollKeyboard()
	{
		HRESULT result;
		result = diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		if (FAILED(result))
		{
			diKeyboard->Acquire();
			diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		}
	}

#pragma endregion Keyboard

#pragma region Mouse
	int Input::InitMouse()
	{
		HRESULT result;
		result = dInput->CreateDevice(GUID_SysMouse, &diMouse, NULL);
		if (FAILED(result))
			return 0;
		result = diMouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result))
			return 0;
		result = diMouse->SetCooperativeLevel((*hWnd), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diMouse->Acquire();
		if (FAILED(result))
			return 0;
		return 1;
	}

	int Input::MouseButtonPress(int mousebutton)
	{
		// log
		int button = mouseState.rgbButtons[mousebutton] & 0x80;
		if (button != 0)
		{
			g_debug.Log("Mouse button is pressed");
			g_debug.Log("Virtual mouse state: " + std::to_string(button));
			g_debug.Log(std::to_string(GetMouseX()) + ", " + std::to_string(GetMouseY()));
		}
		//

		return mouseState.rgbButtons[mousebutton] & 0x80;
	}

	void Input::PollMouse()
	{
		HRESULT result;
		result = diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		if (FAILED(result))
		{
			diMouse->Acquire();
			diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		}
	}

#pragma endregion Mouse
}