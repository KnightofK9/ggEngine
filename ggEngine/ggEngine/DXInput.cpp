#include "DXInput.h"

namespace ggEngine
{
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 diKeyboard;
	LPDIRECTINPUTDEVICE8 diMouse;
	DIMOUSESTATE mouseState;

	char keyStates[256]; // keyboard state buffer

	int InitInputs(HWND hWnd)
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
			return 0;

		// Init Keyboard
		result = dInput->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diKeyboard->Acquire();
		if (FAILED(result))
			return 0;

		// Init mouse
		result = dInput->CreateDevice(GUID_SysMouse, &diKeyboard, NULL);
		if (FAILED(result))
			return;
		result = diMouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result))
			return 0;
		result = diMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diMouse->Acquire();
		if (FAILED(result))
			return 0;

		return 1;
	}

	int IsKeyDown(int keyCode)
	{
		return keyStates[keyCode] & 0x80;
	}

	int GetMouseX() { return mouseState.lX; }
	int GetMouseY() { return mouseState.lY; }

	int IsMouseButtonPress(int mousebutton)
	{
		//return BUTTON_DOWN(mouseState, button);
		return mouseState.rgbButtons[mousebutton] & 0x80;
	}

	void Poll()
	{
		HRESULT result;
		/// Poll keyboard
		result = diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		if (FAILED(result))
		{
			diKeyboard->Acquire();
			diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		}

		/// Poll mouse
		result = diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		if (FAILED(result))
		{
			diMouse->Acquire();
			diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		}
	}

	void ShutDown()
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
}